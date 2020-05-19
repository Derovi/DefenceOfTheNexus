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
    socket->setSocketOption(QAbstractSocket::SendBufferSizeSocketOption, 100000);
    socket->setSocketOption(QAbstractSocket::ReceiveBufferSizeSocketOption, 100000);
    socket->setReadBufferSize(100000);
    QObject::connect(socket.get(), SIGNAL(readyRead()), SLOT(readMessage()));
}

void server::Server::sendMessage(const ConnectedPlayer& connectedPlayer, const QString& message) {
    QThread::create([=] {
        const int offsetConst = 32000;
        int datagramsCount = message.size() / offsetConst + (message.size() % offsetConst != 0);
        for (int offset = 0;
             offset < message.size();
             offset += offsetConst) {
            QByteArray datagram;
            QDataStream out(&datagram, QIODevice::WriteOnly);
            out.setVersion(QDataStream::Qt_5_13);
            out << '<' + QString::number(offset / offsetConst) + ':' +
                   QString::number(datagramsCount) +
                   '*' + QString::number(currentDatagramId) + '>' +
                   message.mid(offset, std::min(offsetConst, message.size() - offset));
            socket->writeDatagram(datagram, QHostAddress(connectedPlayer.getAddress()),
                                  connectedPlayer.getPort());
            qDebug() << "send!" << offset / offsetConst;
            QThread::msleep(100);
        }
        ++currentDatagramId;
    })->start();
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

    if (message.startsWith(utils::network::prefixInitRequest)) {
        initPlayer(getPlayerId(senderAddress, senderPort));
    } else if (message.startsWith(utils::network::prefixSendCommand)) {
        commandReceived(senderAddress, senderPort,
                        message);
    } else if (message.startsWith(utils::network::prefixConnectRequest)) {
        qDebug() << "connect!";
        uint8_t playerId = connectPlayer(senderAddress, senderPort);
        sendMessage(getConnectedPlayer(playerId), utils::network::prefixConnectResponse +
                                                  utils::network::separator +
                                                  QString::number(playerId) +
                                                  utils::network::separator +
                                                  QString::number(
                                                          engine->getGameWorld()->getTeamCount()));
    } else if (message.startsWith(utils::network::prefixRequestNickname)) {
        nickNameRequest(getPlayerId(senderAddress, senderPort), message);
    } else if (message.startsWith(utils::network::prefixRequestSlot)) {
        slotRequest(getPlayerId(senderAddress, senderPort), message);
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
    qDebug() << "start update - server";
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
    qDebug() << "finish update - server";
}

server::Engine* server::Server::getEngine() const {
    return engine;
}

void server::Server::initPlayer(uint8_t playerId) {
    qDebug() << "init" << playerId;
    if (playerId == 255) {
        return;
    }
    ConnectedPlayer* connectedPlayer = nullptr;
    for (auto& player : connectedPlayers) {
        if (player.getId() == playerId) {
            connectedPlayer = &player;
            break;
        }
    }
    qDebug() << "int" << connectedPlayer->getTeam();
    if (connectedPlayer == nullptr || connectedPlayer->getTeam() == 255) {
        return;
    }
    utils::SmartSerializer serializer(false);
    sendMessage(*connectedPlayer, utils::network::prefixInitResponse + utils::network::separator +
                                  serializer.getChanges(std::make_shared<core::GameWorld>(),
                                                        engine->getGameWorld()));
    qDebug() << "suc";
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

void server::Server::nickNameRequest(uint8_t playerId, const QString& message) {
    if (playerId == 255) {
        return;
    }
    ConnectedPlayer* connectedPlayer;
    for (auto& player : connectedPlayers) {
        if (player.getId() == playerId) {
            connectedPlayer = &player;
            break;
        }
    }
    QStringList arguments = message.split(utils::network::separator);  // {prefix, nickname}
    connectedPlayer->setNickname(arguments[1]);
    QString response = utils::network::prefixResponseNickname + utils::network::separator +
                       QString::number(connectedPlayer->getId()) + '#' + arguments[1];
    for (const auto& player : connectedPlayers) {
        sendMessage(player, response);
    }
    qDebug() << "nickname response:" << response;
}

void server::Server::slotRequest(uint8_t playerId, const QString& message) {
    if (playerId == 255) {
        return;
    }
    ConnectedPlayer* connectedPlayer;
    for (auto& player : connectedPlayers) {
        if (player.getId() == playerId) {
            connectedPlayer = &player;
            break;
        }
    }
    QStringList arguments = message.split(utils::network::separator);  // {prefix, nickname}
    int team = arguments[1].toInt();
    qDebug() << "team:" << team;
    bool slotFree = true;
    for (const auto& player : connectedPlayers) {
        if (player.getTeam() == team) {
            slotFree = false;
            break;
        }
    }
    if (!slotFree) {
        return;
    }
    connectedPlayer->setTeam(team);
    QJsonArray responseArray;
    for (int index = 0;
         index < engine->getGameWorld()->getTeamCount() - 1;
         ++index) {
        ConnectedPlayer foundPlayer;
        bool found = false;
        for (const auto& player : connectedPlayers) {
            if (player.getTeam() == index + 1) {
                foundPlayer = player;
                found = true;
                break;
            }
        }
        if (found) {
            responseArray.push_back(
                    QString::number(foundPlayer.getId()) + '#' + foundPlayer.getNickname());
        } else {
            responseArray.push_back("");
        }
    }
    QJsonObject responseJson;
    responseJson.insert("slots", responseArray);
    QString response = utils::Serializer().jsonObjectToString(responseJson);
    std::cout << "response:" << response.toStdString();
    for (const auto& player : connectedPlayers) {
        sendMessage(player,
                    utils::network::prefixTeamUpdate + utils::network::separator + response);
    }
}
