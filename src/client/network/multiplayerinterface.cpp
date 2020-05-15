#include <QtCore/QDataStream>
#include <utility>

#include "multiplayerinterface.h"

#include "../../utils/network.h"
#include "../../utils/serializer.h"
#include "../../utils/smartserializer.h"

client::MultiplayerInterface::MultiplayerInterface(GameScreen* gameScreen, QString address,
                                                   int port):
        address(std::move(address)), port(port), socket(std::make_shared<QUdpSocket>()),
        gameScreen(gameScreen) {
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
    QByteArray Datagram;
    do {
        Datagram.resize(socket->pendingDatagramSize());
        socket->readDatagram(Datagram.data(), Datagram.size());
    } while (socket->hasPendingDatagrams());

    QDataStream in(&Datagram, QIODevice::ReadOnly);
    QString message;
    in >> message;

    qDebug() << "client read message, length: " << message.length();

    if (message.startsWith(utils::network::prefixInitResponse)) {
        initResponse(message);
    } else if (message.startsWith(utils::network::prefixWorldUpdate)) {
        worldUpdate(message);
    }
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
    int teamEntryStart =
            utils::network::prefixInitRequest.size() + utils::network::separator.size();
    QString team = message.mid(teamEntryStart,
                               message.indexOf(utils::network::separator, teamEntryStart) -
                               teamEntryStart);
    int worldJsonEntryStart = teamEntryStart + team.length() + utils::network::separator.size();
    QString worldJson = message.right(message.size() - worldJsonEntryStart);

    gameScreen->setTeam(team.toUInt());

    utils::SmartSerializer serializer;
    serializer.applyChanges(
            std::shared_ptr<core::GameWorld>(gameScreen->getGameMap()->getGameWorld()), worldJson);
}

void client::MultiplayerInterface::worldUpdate(const QString& message) {
    QString worldJson = message.right(message.size() - utils::network::prefixWorldUpdate.size() -
                                      utils::network::separator.size());
    utils::SmartSerializer serializer;
    serializer.applyChanges(
            std::shared_ptr<core::GameWorld>(gameScreen->getGameMap()->getGameWorld()), worldJson);
}

client::GameScreen* client::MultiplayerInterface::getGameScreen() const {
    return gameScreen;
}

void client::MultiplayerInterface::setGameScreen(client::GameScreen* gameScreen) {
    MultiplayerInterface::gameScreen = gameScreen;
}

int client::MultiplayerInterface::getPort() const {
    return port;
}
