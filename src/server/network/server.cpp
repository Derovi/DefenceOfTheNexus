#include <memory>
#include <QtCore/QDataStream>

#include "server.h"
#include "connectedplayer.h"
#include "../../utils/network.h"
#include "../engine.h"
#include "../../utils/smartserializer.h"

server::Server::Server(Engine* engine, int port):
        engine(engine), port(port), commandQueue(engine->getCommandQueue()) {}

void server::Server::registerCommandQueue(std::shared_ptr<Queue<core::Command>> commandQueue) {
    this->commandQueue = commandQueue;
}

void server::Server::start() {
    socket = std::make_shared<QUdpSocket>();
    socket->bind(port);
    QObject::connect(socket.get(), SIGNAL(readyRead()), SLOT(readMessage()));
}

void server::Server::sendMessage(const ConnectedPlayer& connectedPlayer, const QString& message) {
    const int offsetConst = 32085;
    int datagramsCount = message.size() / offsetConst + (message.size() % offsetConst != 0);
    for (int offset = 0;
         offset < message.size();
         offset += offsetConst) {
        QByteArray datagram;
        QDataStream out(&datagram, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_13);
        out << '<' + QString(offset / offsetConst) + ':' + QString(datagramsCount) + '>' +
               message.mid(offset, std::min(offsetConst, message.size() - offset));
        socket->writeDatagram(datagram, QHostAddress(connectedPlayer.getAddress()),
                              connectedPlayer.getPort());
    }
    qDebug() << "message sended from server";
}


void server::Server::readMessage() {
    QByteArray datagram;
    QHostAddress hostAddress;
    quint16 senderPort;
    do {
        datagram.resize(socket->pendingDatagramSize());
        socket->readDatagram(datagram.data(), datagram.size(), &hostAddress, &senderPort);
    } while (socket->hasPendingDatagrams());

    QDataStream in(&datagram, QIODevice::ReadOnly);
    QString message;
    in >> message;

    QString senderAddress = QHostAddress(hostAddress.toIPv4Address()).toString();

    qDebug() << "server read message, length: " << message.length();
    qDebug() << "sender:" << senderAddress << senderPort;

    if (message.startsWith(utils::network::prefixInitRequest)) {
        initPlayer(senderAddress, senderPort);
    } else if (message.startsWith(utils::network::prefixSendCommand)) {
        commandReceived(senderAddress, senderPort,
                        message);
    }
}

void server::Server::finish() {
    // todo server finish
}

std::shared_ptr<Queue<core::Command>> server::Server::getCommandQueue() {
    return commandQueue;
}

int server::Server::getPort() const {
    return port;
}

void server::Server::updateGameWorld() {
    for (const ConnectedPlayer& connectedPlayer : connectedPlayers) {
        utils::SmartSerializer serializer(true);
        qDebug() << "world" << engine->getWorldBeforeUpdate()->getObjects().size()
                 << engine->getGameWorld()->getObjects().size();
        sendMessage(connectedPlayer, utils::network::prefixWorldUpdate + utils::network::separator +
                                     serializer.getChanges(engine->getWorldBeforeUpdate(),
                                                           engine->getGameWorld()));
    }
}

server::Engine* server::Server::getEngine() const {
    return engine;
}

void server::Server::initPlayer(const QString& address, int port) {
    ConnectedPlayer foundPlayer;
    bool isPlayerFound = false;
    for (const ConnectedPlayer& connectedPlayer : connectedPlayers) {
        if (connectedPlayer.getAddress() == address && connectedPlayer.getPort() == port) {
            foundPlayer = connectedPlayer;
            isPlayerFound = true;
            break;
        }
    }
    if (!isPlayerFound) {
        foundPlayer = ConnectedPlayer(address, port, engine->getGameWorld()->getTeamCount());
        engine->getGameWorld()->setTeamCount(engine->getGameWorld()->getTeamCount() + 1);
        connectedPlayers.push_back(foundPlayer);
    }
    utils::Serializer serializer;
    sendMessage(foundPlayer, utils::network::prefixInitResponse + utils::network::separator +
                             QString(foundPlayer.getTeam()) + utils::network::separator +
                             serializer.serializeGameWorld(*engine->getGameWorld()).value());
    qDebug() << "init message";
}

void server::Server::commandReceived(const QString& address, int port, const QString& message) {
    qDebug() << "command received";
    QString commandJson = message.right(message.size() - utils::network::prefixSendCommand.size() -
                                        utils::network::separator.size());
    utils::Serializer serializer;
    if (serializer.deserializeCommand(commandJson) == std::nullopt) {
        qDebug() << "Can't deserialize command!";
        return;
    }
    commandQueue->push(serializer.deserializeCommand(commandJson).value());
}

const std::shared_ptr<QUdpSocket>& server::Server::getSocket() const {
    return socket;
}


