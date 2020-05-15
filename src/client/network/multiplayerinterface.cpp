#include <QtCore/QDataStream>
#include <utility>

#include "multiplayerinterface.h"

#include "../../utils/network.h"
#include "../../utils/serializer.h"

MultiplayerInterface::MultiplayerInterface(QString address, QString port):
        address(std::move(address)), port(std::move(port)), socket(new QUdpSocket()) {
    QObject::connect(socket.get(), SIGNAL(readyRead()), SLOT(readMessage()));
}

void MultiplayerInterface::sendMessage(const QString& message) {
    QByteArray Datagram;
    QDataStream out(&Datagram, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_13);
    out << message;
    socket->writeDatagram(Datagram, QHostAddress::LocalHost, 2424);
}

void MultiplayerInterface::readMessage() {
    QByteArray Datagram;

    do {
        Datagram.resize(socket->pendingDatagramSize());
        socket->readDatagram(Datagram.data(), Datagram.size());
    } while (socket->hasPendingDatagrams());

    QDataStream in(&Datagram, QIODevice::ReadOnly);
    QString message;
    in >> message;
}

void MultiplayerInterface::sendCommand(const core::Command& command) {
    utils::Serializer serializer;
    sendMessage(utils::network::prefixSendCommand +
                utils::network::separator +
                serializer.serializeCommand(command).value());
}

const QString& MultiplayerInterface::getAddress() const {
    return address;
}

const QString& MultiplayerInterface::getPort() const {
    return port;
}

const std::shared_ptr<QUdpSocket>& MultiplayerInterface::getSocket() const {
    return socket;
}
