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
    qint64 lastTick = QDateTime::currentDateTime().currentMSecsSinceEpoch();
    mainThread = QThread::create([&] {
        while (true) {
            if (finished) {
                break;
            }

            qint64 timeBeforeTick = QDateTime::currentDateTime().currentMSecsSinceEpoch();

            // firstly, execute all commands from clients
            executeCommands();
            // make changes on game world
            gameWorldController->tick(1.0 / static_cast<double>(timeBeforeTick - lastTick));

            qint64 currentTime = QDateTime::currentDateTime().currentMSecsSinceEpoch();

            // sleep until next tick
            mainThread->msleep(1000 / gameConfiguration.getTickPerSec() -
                               (currentTime - timeBeforeTick));
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
