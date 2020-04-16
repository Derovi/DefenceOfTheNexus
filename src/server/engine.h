#ifndef ENGINE_H
#define ENGINE_H

#include <QThread>

#include "../core/gameworld.h"
#include "../core/command.h"

#include "gameconfiguration.h"
#include "controllers/gameworldcontroller.h"
#include "commandexecutor.h"

namespace server {

class Engine {
  public:
    explicit Engine(const GameConfiguration& gameConfiguration);

    void start();

    std::shared_ptr<core::GameWorld> getGameWorld();

    std::shared_ptr<GameWorldController> getGameWorldController();

    const GameConfiguration& getGameConfiguration() const;

    std::shared_ptr<QThread> getMainThread() const;

    std::shared_ptr<QQueue<core::Command>> getCommandQueue() const;

    void finish();

    bool isFinished() const;

    ~Engine();

  private:
    std::shared_ptr<core::GameWorld> gameWorld;
    std::shared_ptr<GameWorldController> gameWorldController;
    CommandExecutor commandExecutor;
    GameConfiguration gameConfiguration;
    std::shared_ptr<QThread> mainThread;
    std::atomic<bool> finished = false;

    // todo fix race-condition
    std::shared_ptr<QQueue<core::Command>> commandQueue;

    void executeCommands();
};

}

#endif //ENGINE_H