#include <memory>
#include <QtCore/QDataStream>

#include "server.h"

server::Server::Server(int port) : port(port) {}

void server::Server::registerCommandQueue(std::shared_ptr<Queue<core::Command>> commandQueue) {
    this->commandQueue = commandQueue;
}

void server::Server::start() {
    socket = std::make_shared<QUdpSocket>(QUdpSocket());
    socket->bind(port);
    QObject::connect(socket.get(), SIGNAL(readyRead()), SLOT(readMessage()));
}

void server::Server::sendMessage(const ConnectedPlayer& connectedPlayer, const QString& message) {
    QByteArray Datagram;
    QDataStream out(&Datagram, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_13);
    out << message;
    socket->writeDatagram(Datagram, QHostAddress(address), port);
}


void server::Server::readMessage() {
    QByteArray Datagram;
    do {
        Datagram.resize(socket->pendingDatagramSize());
        socket->readDatagram(Datagram.data(), Datagram.size());
    } while (socket->hasPendingDatagrams());

    QDataStream in(&Datagram, QIODevice::ReadOnly);
    QString message;
    in >> message;

    if (message.startsWith(utils::network::prefixInitResponse)) {
        initResponse(message);
    } else if (message.startsWith(utils::network::prefixWorldUpdate)) {
        worldUpdate(message);
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


