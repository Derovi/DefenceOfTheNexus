#include <QtCore/QDataStream>
#include <utility>

#include "multiplayerinterface.h"

#include "../../utils/network.h"
#include "../../utils/serializer.h"
#include "../../utils/smartserializer.h"

client::MultiplayerInterface::MultiplayerInterface(QString address, int port):
        address(std::move(address)), port(port), socket(std::make_shared<QUdpSocket>()), team(255), gameWorld(new core::GameWorld()) {
    QObject::connect(socket.get(), SIGNAL(readyRead()), SLOT(readMessage()));
}

void client::MultiplayerInterface::sendMessage(const QString& message) {
    QByteArray Datagram;
    QDataStream out(&Datagram, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_13);
    out << message;
    socket->writeDatagram(Datagram, QHostAddress(address), port);
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
        int messageStart = message.indexOf('>') + 1;

        //qDebug() << "mes st" << messageStart << message.length();
        int dataGramIndex = message.mid(1, datagramCountStart - 2).toInt();
        int dataGramCount = message.mid(datagramCountStart, messageStart - datagramCountStart - 1).toInt();
        //qDebug() << "index:" << dataGramIndex << dataGramCount << message.size();
        message = message.right(message.size() - messageStart);
        qDebug() << "client read message, length: " << message.length();
        std::cout << message.toStdString() << std::endl;

        if (message.startsWith(utils::network::prefixInitResponse)) {
            initResponse(message);
        } else if (message.startsWith(utils::network::prefixWorldUpdate)) {
            worldUpdate(message);
        } else if (message.startsWith(utils::network::prefixEvent)) {
            eventReceived(message);
        }
    } while (socket->hasPendingDatagrams());
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
    sendMessage(utils::network::prefixInitRequest);
}

void client::MultiplayerInterface::initResponse(const QString& message) {
    qDebug() << "init response!";
    int teamEntryStart =
            utils::network::prefixInitRequest.size() + utils::network::separator.size();
    QString team = message.mid(teamEntryStart,
                               message.indexOf(utils::network::separator, teamEntryStart) -
                               teamEntryStart);
    int worldJsonEntryStart = teamEntryStart + team.length() + utils::network::separator.size();
    QString worldJson = message.right(message.size() - worldJsonEntryStart);

    this->team = team.toUInt();

    utils::SmartSerializer serializer(false);
    qDebug() << "applying changes!!";
    qDebug()<<worldJson;
    serializer.applyChanges(gameWorld, worldJson);
    qDebug() << "emit inited!";
    emit inited();
}

void client::MultiplayerInterface::worldUpdate(const QString& message) {
    QString worldJson = message.right(message.size() - utils::network::prefixWorldUpdate.size() -
                                      utils::network::separator.size());
    utils::SmartSerializer serializer(false);
    serializer.applyChanges(gameWorld, worldJson);
    qDebug() << "changed applied!";
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
