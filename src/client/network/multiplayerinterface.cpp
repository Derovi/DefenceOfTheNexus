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

        //qDebug() << "mes st" << messageStart << message.length();
        int dataGramIndex = message.mid(1, datagramCountStart - 2).toInt();
        int dataGramCount = message.mid(datagramCountStart,
                                        datagramIdStart - datagramCountStart - 1).toInt();
        int dataGramId = message.mid(datagramIdStart, messageStart - datagramIdStart - 1).toInt();
//        qDebug() << "index:" << dataGramIndex << ' ' <<  dataGramCount <<  ' ' << dataGramId << ' ' << message.size() << endl;
        message = message.right(message.size() - messageStart);
//        qDebug() << "client read message, length: " << message.length();
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
    sendMessage(
            utils::network::prefixInitRequest + utils::network::separator + QString::number(team));
}

void client::MultiplayerInterface::initResponse(const QString& message) {
    qDebug() << "init response!";
    int teamEntryStart =
            utils::network::prefixInitResponse.size() + utils::network::separator.size();
    QString team = message.mid(teamEntryStart,
                               message.indexOf(utils::network::separator, teamEntryStart) -
                               teamEntryStart);
//    qDebug() << "init response team: " << team;
    int worldJsonEntryStart = teamEntryStart + team.length() + utils::network::separator.size();
    QString worldJson = message.right(message.size() - worldJsonEntryStart);

    this->team = team.toUInt();

    utils::SmartSerializer serializer(false);
//    qDebug() << "applying changes!!";
    serializer.applyChanges(gameWorld, worldJson);
//    qDebug() << "emit inited!";
    emit inited();
}

void client::MultiplayerInterface::worldUpdate(const QString& message) {
    QString worldJson = message.right(message.size() - utils::network::prefixWorldUpdate.size() -
                                      utils::network::separator.size());
    utils::SmartSerializer serializer(false);
    serializer.applyChanges(gameWorld, worldJson);
//    qDebug() << "changed applied!";
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
//                qDebug() << "timeout, datagram parts lost!";
                datagrams.clear();
                if (state == State::IN_GAME) {
                    sendInitRequest();
                }
            }
            return;
        }
        datagrams.remove(datagrams.firstKey());
        if (message.startsWith(utils::network::prefixInitResponse)) {
            initResponse(message);
        } else if (message.startsWith(utils::network::prefixWorldUpdate)) {
            worldUpdate(message);
        } else if (message.startsWith(utils::network::prefixEvent)) {
            eventReceived(message);
        } else if (message.startsWith(utils::network::prefixConnectResponse)) {
            connectResponse(message);
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
