#include "engine.h"

#include <QDateTime>
#include <QThread>

#include "../utils/queue.h"
#include "../core/gameworld.h"
#include "../core/command.h"

#include "commandexecutor.h"
#include "worldgenerator.h"

server::Engine::Engine(const GameConfiguration& gameConfiguration):
    gameConfiguration(gameConfiguration), finished(false) {
    gameWorld = world_generator::generate(gameConfiguration);
    gameWorldController = std::make_shared<GameWorldController>(gameWorld);
    commandExecutor = CommandExecutor(gameWorldController);
    commandQueue = std::make_shared<Queue<core::Command>>();
}

server::Engine::~Engine() {
    mainThread->quit();
}

void server::Engine::start() {
    mainThread = std::shared_ptr<QThread>(QThread::create([&] {
        QDateTime lastTickStartTime = QDateTime::currentDateTime();
        while (!finished && gameWorld != nullptr) {
            QDateTime currentTickStartTime = QDateTime::currentDateTime();

            executeCommands();
            // make changes on game world
            gameWorldController->tick(lastTickStartTime.msecsTo(currentTickStartTime));

            lastTickStartTime = currentTickStartTime;
            // sleep until next tick
            QThread::msleep(1000 / gameConfiguration.getTickPerSec() -
                currentTickStartTime.msecsTo(QDateTime::currentDateTime()));
        }
    }));
    mainThread->start();
}

std::shared_ptr<core::GameWorld> server::Engine::getGameWorld() {
    return gameWorld;
}

std::shared_ptr<server::GameWorldController> server::Engine::getGameWorldController() {
    return gameWorldController;
}

const GameConfiguration& server::Engine::getGameConfiguration() const {
    return gameConfiguration;
}

std::shared_ptr<QThread> server::Engine::getMainThread() const {
    return mainThread;
}

void server::Engine::finish() {
    finished = true;
    mainThread->wait();
}

bool server::Engine::isFinished() const {
    return finished;
}

std::shared_ptr<Queue<core::Command>> server::Engine::getCommandQueue() const {
    return commandQueue;
}

void server::Engine::executeCommands() {
    while (!commandQueue->empty()) {
        commandExecutor.executeCommand(commandQueue->pop());
    }
}

void server::Engine::setGameWorld(const std::shared_ptr<core::GameWorld>& gameWorld) {
    this->gameWorld = gameWorld;
    gameWorldController = std::make_shared<GameWorldController>(gameWorld);
    commandExecutor = CommandExecutor(gameWorldController);
    commandQueue = std::make_shared<Queue<core::Command>>();
}
