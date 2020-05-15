#include <memory>
#include <QtCore/QDataStream>

#include "server.h"
#include "connectedplayer.h"
#include "../../utils/network.h"
#include "../engine.h"
#include "../../utils/smartserializer.h"

server::Server::Server(Engine* engine, int port): engine(eingine), port(port) {}

void server::Server::registerCommandQueue(std::shared_ptr<Queue<core::Command>> commandQueue) {
    this->commandQueue = commandQueue;
}

void server::Server::start() {
    socket = std::make_shared<QUdpSocket>();
    socket->bind(port);
    QObject::connect(socket.get(), SIGNAL(readyRead()), SLOT(readMessage()));
}

void server::Server::sendMessage(const ConnectedPlayer& connectedPlayer, const QString& message) {
    QByteArray Datagram;
    QDataStream out(&Datagram, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_13);
    out << message;
    socket->writeDatagram(Datagram, QHostAddress(connectedPlayer.getAddress()),
                          connectedPlayer.getPort());
}


void server::Server::readMessage() {
    QByteArray datagram;
    QHostAddress senderAddress;
    quint16 senderPort;
    do {
        datagram.resize(socket->pendingDatagramSize());
        socket->readDatagram(datagram.data(), datagram.size(), &senderAddress, &senderPort);
    } while (socket->hasPendingDatagrams());

    QDataStream in(&datagram, QIODevice::ReadOnly);
    QString message;
    in >> message;

    if (message.startsWith(utils::network::prefixInitRequest)) {
        initPlayer(QHostAddress(senderAddress.toIPv4Address()).toString(), senderPort);
    } else if (message.startsWith(utils::network::prefixSendCommand)) {
        commandReceived(QHostAddress(senderAddress.toIPv4Address()).toString(), senderPort,
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
        utils::SmartSerializer serializer(false);
        sendMessage(connectedPlayer, utils::network::prefixWorldUpdate + utils::network::separator +
                                     serializer.getChanges(engine->getGameWorld(),
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
}

void server::Server::commandReceived(const QString& address, int port, const QString& message) {
    QString commandJson = message.right(message.size() - utils::network::prefixSendCommand.size() -
                                      utils::network::separator.size());
    utils::Serializer serializer;
    if (serializer.deserializeCommand(commandJson) == std::nullopt) {
        qDebug() << "Can't deserialize command!";
        return;
    }
    commandQueue->push(serializer.deserializeCommand(commandJson).value());
}


