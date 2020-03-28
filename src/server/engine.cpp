#include <QDateTime>
#include <QThread>
#include <QQueue>
#include <QDebug>
#include <QDateTime>

#include "../core/gameworld.h"
#include "../core/command.h"

#include "commandexecutor.h"
#include "engine.h"
#include "worldgenerator.h"

server::Engine::Engine(const GameConfiguration& gameConfiguration):
        gameConfiguration(gameConfiguration) {
    gameWorld = world_generator::generate(gameConfiguration);
    gameWorldController = new GameWorldController(gameWorld);
    commandExecutor = CommandExecutor(gameWorld);
    commandQueue = new QQueue<core::Command>();
}

void server::Engine::start() {
    mainThread = QThread::create([&] {
        // time when last tick execution was started
        QDateTime lastTickStartTime = QDateTime::currentDateTime();
        while (true) {
            if (finished) {
                break;
            }

            QDateTime currentTickStartTime = QDateTime::currentDateTime();

            // first, execute all commands from clients
            executeCommands();
            // make changes on game world
            gameWorldController->tick(static_cast<double>(
                                              lastTickStartTime.msecsTo(currentTickStartTime)));

            // sleep until next tick
            QThread::msleep(1000 / gameConfiguration.getTickPerSec() -
                               currentTickStartTime.msecsTo(QDateTime::currentDateTime()));

            lastTickStartTime = currentTickStartTime;
        }
    });
    mainThread->start();
}

core::GameWorld* server::Engine::getGameWorld() {
    return gameWorld;
}

server::GameWorldController* server::Engine::getGameWorldController() {
    return gameWorldController;
}

const GameConfiguration& server::Engine::getGameConfiguration() const {
    return gameConfiguration;
}

QThread* server::Engine::getMainThread() const {
    return mainThread;
}

void server::Engine::finish() {
    finished = true;
}

bool server::Engine::isFinished() const {
    return finished;
}

QQueue<core::Command>* server::Engine::getCommandQueue() const {
    return commandQueue;
}

void server::Engine::executeCommands() {
    while (!commandQueue->empty()) {
        commandExecutor.executeCommand(commandQueue->front());
        commandQueue->pop_front();
    }
}

server::Engine::~Engine() {
    mainThread->quit();
    if (gameWorld) {
        delete gameWorld;
        gameWorld = nullptr;
    }
    if (gameWorldController) {
        delete gameWorldController;
        gameWorldController = nullptr;
    }
}
