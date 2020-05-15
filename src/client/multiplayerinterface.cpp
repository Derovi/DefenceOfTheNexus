#include "multiplayerinterface.h"

MultiplayerInterface::MultiplayerInterface() : socket(new QUdpSocket()) {}

void MultiplayerInterface::start() {
    socket->bind(45454, QUdpSocket::ShareAddress);
    connect(socket.get(), &QIODevice::readyRead, this, &MultiplayerInterface::onReadyRead);
}

void MultiplayerInterface::onReadyRead() {
    QByteArray datagram;
    while (socket->hasPendingDatagrams()) {
        datagram.resize(100);
        socket->readDatagram(datagram.data(), 100);
        qInfo() << "receive:" << datagram.toStdString().c_str();
    }
}