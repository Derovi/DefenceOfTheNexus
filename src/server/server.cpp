#include <memory>

#include "server.h"

void server::Server::registerCommandQueue(std::shared_ptr<Queue<core::Command>> commandQueue) {
    Server::commandQueue = commandQueue;
}

void server::Server::start() {
    // todo server start
}

void server::Server::finish() {
    // todo server finish
}

std::shared_ptr<Queue<core::Command>> server::Server::getCommandQueue() {
    return commandQueue;
}
