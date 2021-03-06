#include <QtCore/QDataStream>
#include <utility>

#include "multiplayerinterface.h"

#include "../../utils/network.h"
#include "../../utils/serializer.h"
#include "../../utils/smartserializer.h"

client::MultiplayerInterface::MultiplayerInterface(QString address, int port, State state):
        address(std::move(address)), port(port), socket(std::make_shared<QUdpSocket>()), team(255),
        gameWorld(new core::GameWorld()), state(state), playerId(255) {
    QObject::connect(socket.get(), SIGNAL(readyRead()), SLOT(readMessage()));
    socket->setSocketOption(QAbstractSocket::SendBufferSizeSocketOption, 100000);
    socket->setSocketOption(QAbstractSocket::ReceiveBufferSizeSocketOption, 100000);
    socket->setReadBufferSize(100000);

    int bufferSize = 32*1024;
}

void client::MultiplayerInterface::sendMessage(const QString& message) {
    QByteArray Datagram;
    QDataStream out(&Datagram, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_13);
    out << message;
    socket->writeDatagram(Datagram, QHostAddress(address), port);
}

void client::MultiplayerInterface::setTeam(uint8_t team) {
    MultiplayerInterface::team = team;
}

void client::MultiplayerInterface::readMessage() {
    //qDebug() << "pend" << socket->pendingDatagramSize();
    do {
        QByteArray Datagram;
        Datagram.resize(socket->pendingDatagramSize());
        socket->readDatagram(Datagram.data(), Datagram.size());
        QDataStream in(&Datagram, QIODevice::ReadOnly);
        QString message;
        in >> message;

        int datagramCountStart = message.indexOf(':') + 1;
        int datagramIdStart = message.indexOf('*') + 1;
        int messageStart = message.indexOf('>') + 1;

        ////qDebug() << "mes st" << messageStart << message.length();
        int dataGramIndex = message.mid(1, datagramCountStart - 2).toInt();
        int dataGramCount = message.mid(datagramCountStart,
                                        datagramIdStart - datagramCountStart - 1).toInt();
        int dataGramId = message.mid(datagramIdStart, messageStart - datagramIdStart - 1).toInt();
        //qDebug() << "index:" << dataGramIndex << ' ' <<  dataGramCount <<  ' ' << dataGramId << ' ' << message.size() << endl;
        message = message.right(message.size() - messageStart);
        //qDebug() << "client read message, length: " << message.length();
        //std::cout << message.toStdString() << std::endl;

        if (!datagrams.contains(dataGramId)) {
            datagrams[dataGramId] = std::make_pair(QVector<QString>(dataGramCount),
                                                   QDateTime::currentDateTime());
        }
        datagrams[dataGramId].first[dataGramIndex] = message;
    } while (socket->hasPendingDatagrams());
    buildDatagrams();
}

void client::MultiplayerInterface::sendCommand(const core::Command& command) {
    utils::Serializer serializer;
    sendMessage(utils::network::prefixSendCommand +
                utils::network::separator +
                serializer.serializeCommand(command).value());
}

const QString& client::MultiplayerInterface::getAddress() const {
    return address;
}

const std::shared_ptr<QUdpSocket>& client::MultiplayerInterface::getSocket() const {
    return socket;
}

void client::MultiplayerInterface::sendInitRequest() {
    //qDebug() << "init request!";
    sendMessage(utils::network::prefixInitRequest);
}

void client::MultiplayerInterface::initResponse(const QString& message) {
    //qDebug() << "init response!";
    auto arguments = message.split(utils::network::separator);  // {prefix, worldJson}

    utils::SmartSerializer serializer(false);
    serializer.applyChanges(gameWorld, arguments[1]);
    emit inited();
    state = IN_GAME;
}

void client::MultiplayerInterface::worldUpdate(const QString& message) {
    if (state != IN_GAME) {
        return;
    }
    //qDebug() << "start update - client";
    QString worldJson = message.right(message.size() - utils::network::prefixWorldUpdate.size() -
                                      utils::network::separator.size());
    utils::SmartSerializer serializer(false);
    serializer.applyChanges(gameWorld, worldJson);
    //qDebug() << "stop update - client";
//    //qDebug() << "changed applied!";
    //std::cout << worldJson.toStdString();
}

int client::MultiplayerInterface::getPort() const {
    return port;
}

const std::shared_ptr<core::GameWorld>& client::MultiplayerInterface::getGameWorld() const {
    return gameWorld;
}

bool client::MultiplayerInterface::isReady() {
    return team < 255;
}

uint8_t client::MultiplayerInterface::getTeam() const {
    return team;
}

QQueue<core::Event>& client::MultiplayerInterface::getEventQueue() {
    return eventQueue;
}

void client::MultiplayerInterface::eventReceived(const QString& message) {
    int eventJsonStart = utils::network::prefixEvent.size() + utils::network::separator.size();
    QString eventJson = message.right(message.size() - eventJsonStart);
    utils::Serializer serializer;
    eventQueue.push_back(serializer.deserializeEvent(eventJson).value());
}

void client::MultiplayerInterface::buildDatagrams() {
    while (!datagrams.empty()) {
        QString message;
        bool completed = true;
        for (const QString& datagram : datagrams.first().first) {
            if (datagram.isEmpty()) {
                completed = false;
                break;
            }
            message += datagram;
        }
        if (!completed) {
            if (datagrams.first().second.msecsTo(QDateTime::currentDateTime()) > timeout) {
                //qDebug() << "timeout, datagram parts lost!";
                datagrams.clear();
                if (state == State::IN_GAME) {
                    sendInitRequest();
                }
            }
            return;
        }
        datagrams.remove(datagrams.firstKey());
        //qDebug() << "completed!" << message.size();
        if (message.startsWith(utils::network::prefixInitResponse)) {
            initResponse(message);
        } else if (message.startsWith(utils::network::prefixWorldUpdate)) {
            worldUpdate(message);
        } else if (message.startsWith(utils::network::prefixEvent)) {
            eventReceived(message);
        } else if (message.startsWith(utils::network::prefixConnectResponse)) {
            connectResponse(message);
        } else if (message.startsWith(utils::network::prefixResponseNickname)) {
            nickNameResponse(message);
        } else if (message.startsWith(utils::network::prefixTeamUpdate)) {
            teamUpdate(message);
        }
    }
}

client::MultiplayerInterface::State client::MultiplayerInterface::getState() const {
    return state;
}

int client::MultiplayerInterface::getPlayerId() const {
    return playerId;
}

void client::MultiplayerInterface::sendConnectRequest() {
    sendMessage(utils::network::prefixConnectRequest);
}

void client::MultiplayerInterface::connectResponse(const QString& message) {
    auto list = message.split(utils::network::separator);  // {prefix, playerId, teamCount}
    playerId = list[1].toInt();
    emit connected(list[2].toInt());
}

void client::MultiplayerInterface::requestNickname(const QString& nickname) {
    sendMessage(utils::network::prefixRequestNickname + utils::network::separator + nickname);
}

void client::MultiplayerInterface::requestSlot(uint8_t slot) {
    sendMessage(
            utils::network::prefixRequestSlot + utils::network::separator + QString::number(slot));
}

void client::MultiplayerInterface::nickNameResponse(const QString& message) {
    auto arguments = message.split(utils::network::separator);  // {prefix, nickname}
    emit nicknameUpdated(arguments[1]);
}

void client::MultiplayerInterface::teamUpdate(const QString& message) {
    auto arguments = message.split(utils::network::separator);  // {prefix, array json}
    //qDebug() << "team update!! ";
    QJsonArray jsonArray = utils::Serializer().stringToJsonObject(arguments[1]).value()["slots"].toArray();
    QVector<QString> result;
    uint8_t textIndex = 0;
    for (auto variant : jsonArray.toVariantList()) {
        QString line = variant.toString();
        std::cout << "line " << line.toStdString() << std::endl;
        result.push_back(line);
        if (!line.isEmpty()) {
            int id = line.right(line.indexOf('#')).toInt();
            std::cout << id << std::endl;
            if (id == getPlayerId()) {
                std::cout << "match" << (int) textIndex;
                setTeam(textIndex + 1);
            }
        }
        ++textIndex;
    }
    emit slotsUpdated(result);
}
