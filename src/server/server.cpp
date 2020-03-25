//
// Created by derovi on 3/25/2020.
//

#include "server.h"

QQueue<core::Command>* server::Server::getCommandQueue() const {
    return commandQueue;
}

void server::Server::registerCommandQueue(QQueue<core::Command>* commandQueue) {
    Server::commandQueue = commandQueue;
}

void server::Server::start() {

}

void server::Server::finish() {

}
