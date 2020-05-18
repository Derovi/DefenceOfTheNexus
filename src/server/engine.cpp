#include "engine.h"

#include <chrono>

#include <QDateTime>
#include <QThread>

#include "../utils/queue.h"
#include "../core/gameworld.h"
#include "../core/command.h"
#include "../core/event.h"
#include "../client/app.h"

#include "ai/simpleai.h"
#include "commandexecutor.h"
#include "worldgenerator.h"

server::Engine::Engine(const GameConfiguration& gameConfiguration):
        gameConfiguration(gameConfiguration), finished(false), mainThread(nullptr) {
    gameWorld = world_generator::generate(gameConfiguration);
    worldBeforeUpdate = std::make_shared<core::GameWorld>();
    gameWorldController = std::make_shared<GameWorldController>(gameWorld, this);
    commandExecutor = CommandExecutor(gameWorldController);
    commandQueue = std::make_shared<Queue<core::Command>>();
    addAIPlayer(std::make_shared<server::SimpleAI>(this, 0));
}

server::Engine::~Engine() {
    if (mainThread != nullptr) {
        mainThread->quit();
    }
}

void server::Engine::start() {
    mainThread = std::shared_ptr<QThread>(QThread::create([&] {
        auto lastTickStartTime = std::chrono::steady_clock::now();
        while (!finished && gameWorld != nullptr) {
            worldBeforeUpdate = std::make_shared<core::GameWorld>(*gameWorld);
            auto currentTickStartTime = std::chrono::steady_clock::now();
            executeCommands();
            int deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(
                    currentTickStartTime - lastTickStartTime).count();
            for (auto& aiPlayer : aiPlayers) {
                aiPlayer->tick(deltaTime);
            }
            // make changes on game world
            gameWorldController->tick(deltaTime);

            lastTickStartTime = currentTickStartTime;

            // sleep until next tick
            int sleepTime = 1000 / gameConfiguration.getTickPerSec() -
                            std::chrono::duration_cast<std::chrono::milliseconds>(
                                    std::chrono::steady_clock::now() -
                                    currentTickStartTime).count();
            if (sleepTime > 0) {
                QThread::msleep(sleepTime);
            }
            emit updated(events);
            events.clear();
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
    gameWorldController = std::make_shared<GameWorldController>(gameWorld, this);
    commandExecutor = CommandExecutor(gameWorldController);
    commandQueue = std::make_shared<Queue<core::Command>>();
}

const std::shared_ptr<core::GameWorld>& server::Engine::getWorldBeforeUpdate() const {
    return worldBeforeUpdate;
}

void server::Engine::generateEvent(const core::Event& event) {
    events.push_back(event);
}

void server::Engine::addAIPlayer(const std::shared_ptr<AIPlayer>& aiPlayer) {
    aiPlayers.push_back(aiPlayer);
}
