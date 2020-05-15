#include <QtCore/QDataStream>
#include "multiplayerinterface.h"

MultiplayerInterface::MultiplayerInterface() : socket(new QUdpSocket()) {
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
    sendMessage("send_command", command);
}
