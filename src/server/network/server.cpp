#include <memory>
#include <QtCore/QDataStream>

#include "server.h"
#include "connectedplayer.h"
#include "../../utils/network.h"
#include "../engine.h"
#include "../../utils/smartserializer.h"

server::Server::Server(Engine* engine, int port):
        engine(engine), port(port), commandQueue(engine->getCommandQueue()), currentDatagramId(0) {}

void server::Server::registerCommandQueue(std::shared_ptr<Queue<core::Command>> commandQueue) {
    this->commandQueue = commandQueue;
}

void server::Server::start() {
    socket = std::make_shared<QUdpSocket>();
    socket->bind(port);
    QObject::connect(socket.get(), SIGNAL(readyRead()), SLOT(readMessage()));
}

void server::Server::sendMessage(const ConnectedPlayer& connectedPlayer, const QString& message) {
    const int offsetConst = 800;
    int datagramsCount = message.size() / offsetConst + (message.size() % offsetConst != 0);
    qDebug() << "cur id" << currentDatagramId;
    for (int offset = 0;
         offset < message.size();
         offset += offsetConst) {
        QByteArray datagram;
        QDataStream out(&datagram, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_13);
        out << '<' + QString::number(offset / offsetConst) + ':' + QString::number(datagramsCount) +
               '*' + QString::number(currentDatagramId) + '>' +
               message.mid(offset, std::min(offsetConst, message.size() - offset));
        socket->writeDatagram(datagram, QHostAddress(connectedPlayer.getAddress()),
                              connectedPlayer.getPort());
    }
    ++currentDatagramId;
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
        initPlayer(senderAddress, senderPort,
                   message.right(message.size() - utils::network::prefixInitRequest.size() -
                                 utils::network::separator.size()).toInt());
    } else if (message.startsWith(utils::network::prefixSendCommand)) {
        commandReceived(senderAddress, senderPort,
                        message);
    } else if (message.startsWith(utils::network::prefixConnectRequest)) {
        qDebug() << "connect!";
        uint8_t playerId = connectPlayer(senderAddress, senderPort);
        sendMessage(getConnectedPlayer(playerId), utils::network::prefixConnectResponse +
                                                  utils::network::separator +
                                                  QString::number(playerId));
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

void server::Server::updateGameWorld(QVector<core::Event> events) {
    for (const ConnectedPlayer& connectedPlayer : connectedPlayers) {
        utils::Serializer serializer;
        for (const core::Event& event : events) {
            sendMessage(connectedPlayer, utils::network::prefixEvent + utils::network::separator +
                                         serializer.serializeEvent(event).value());
        }
        utils::SmartSerializer smartSerializer(false);
        qDebug() << "world" << engine->getWorldBeforeUpdate()->getObjects().size()
                 << engine->getGameWorld()->getObjects().size();
        sendMessage(connectedPlayer, utils::network::prefixWorldUpdate + utils::network::separator +
                                     smartSerializer.getChanges(engine->getWorldBeforeUpdate(),
                                                                engine->getGameWorld()));
    }
}

server::Engine* server::Server::getEngine() const {
    return engine;
}

void server::Server::initPlayer(const QString& address, int port, int team) {
    //TODO INIT PLAYER
    /*ConnectedPlayer foundPlayer;
    bool isPlayerFound = false;
    for (const ConnectedPlayer& connectedPlayer : connectedPlayers) {
        if (connectedPlayer.getAddress() == address && connectedPlayer.getPort() == port) {
            foundPlayer = connectedPlayer;
            isPlayerFound = true;
            break;
        }
    }
    if (!isPlayerFound) {
        foundPlayer = ConnectedPlayer(address, port, team);
        connectedPlayers.push_back(foundPlayer);
    }
    qDebug() << "init message";
    utils::SmartSerializer serializer(false);
    sendMessage(foundPlayer, utils::network::prefixInitResponse + utils::network::separator +
                             QString::number(foundPlayer.getTeam()) + utils::network::separator +
                             serializer.getChanges(std::make_shared<core::GameWorld>(),
                                                   engine->getGameWorld()));*/
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

int server::Server::getCurrentDatagramId() const {
    return currentDatagramId;
}

uint8_t server::Server::getPlayerId(const QString& address, int port) {
    for (const ConnectedPlayer& connectedPlayer : connectedPlayers) {
        if (connectedPlayer.getAddress() == address && connectedPlayer.getPort() == port) {
            return connectedPlayer.getId();
        }
    }
    return 255;
}

uint8_t server::Server::connectPlayer(const QString& address, int port) {
    int playerId = getPlayerId(address, port);
    if (playerId != 255) {
        return playerId;
    }
    playerId = connectedPlayers.size();
    connectedPlayers.push_back(ConnectedPlayer(address, port, 255, playerId));
    return playerId;
}

server::ConnectedPlayer server::Server::getConnectedPlayer(uint8_t id) {
    for (const ConnectedPlayer& connectedPlayer : connectedPlayers) {
        if (connectedPlayer.getId() == id) {
            return connectedPlayer;
        }
    }
    return ConnectedPlayer();
}


