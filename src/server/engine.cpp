#include <QDateTime>
#include <QThread>
#include <QQueue>
#include <QDebug>

#include "../core/gameworld.h"
#include "../core/command.h"

#include "commandexecutor.h"
#include "engine.h"
#include "worldgenerator.h"

server::Engine::Engine(const GameConfiguration& gameConfiguration):
        gameConfiguration(gameConfiguration) {
    gameWorld = WorldGenerator::generate(gameConfiguration);
    gameWorldController = new GameWorldController(gameWorld);
    commandExecutor = CommandExecutor(gameWorld);
    commandQueue = new QQueue<core::Command>();
}

void server::Engine::start() {
    mainThread = QThread::create([&] {
        // time when last tick execution was started
        qint64 lastTickStartTime = QDateTime::currentDateTime().currentMSecsSinceEpoch();
        while (true) {
            if (finished) {
                break;
            }

            qint64 currentTickStartTime = QDateTime::currentDateTime().currentMSecsSinceEpoch();

            // first, execute all commands from clients
            executeCommands();
            // make changes on game world
            gameWorldController->tick(static_cast<double>(
                                              currentTickStartTime - lastTickStartTime));

            // sleep until next tick
            mainThread->msleep(1000 / gameConfiguration.getTickPerSec() -
                               (QDateTime::currentDateTime().currentMSecsSinceEpoch()
                                - currentTickStartTime));


            lastTickStartTime = currentTickStartTime;
        }
    });
    mainThread->start();
}

core::GameWorld* server::Engine::getGameWorld() const {
    return gameWorld;
}

server::GameWorldController* server::Engine::getGameWorldController() const {
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
