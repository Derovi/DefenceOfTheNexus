#include "server.h"

void server::Server::registerCommandQueue(QQueue<core::Command>* commandQueue) {
    Server::commandQueue = commandQueue;
}

void server::Server::start() {
    // todo server start
}

void server::Server::finish() {
    // todo server finish
}

QQueue<core::Command>* server::Server::getCommandQueue() {
    return commandQueue;
}