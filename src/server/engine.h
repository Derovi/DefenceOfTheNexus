#ifndef ENGINE_H
#define ENGINE_H

#include <QThread>

#include "../utils/queue.h"
#include "../core/gameworld.h"
#include "../core/command.h"
#include "controllers/gameworldcontroller.h"

#include "gameconfiguration.h"
#include "commandexecutor.h"

namespace server {

class Engine {
  public:
    explicit Engine(const GameConfiguration& gameConfiguration);

    ~Engine();

    void start();

    std::shared_ptr<core::GameWorld> getGameWorld();

    std::shared_ptr<GameWorldController> getGameWorldController();

    const GameConfiguration& getGameConfiguration() const;

    std::shared_ptr<QThread> getMainThread() const;

    std::shared_ptr<Queue<core::Command>> getCommandQueue() const;

    void setGameWorld(const std::shared_ptr<core::GameWorld>& gameWorld);

    void finish();

    bool isFinished() const;

  private:
    void executeCommands();

    CommandExecutor commandExecutor;
    GameConfiguration gameConfiguration;
    std::atomic_bool finished;
    std::shared_ptr<core::GameWorld> gameWorld;
    std::shared_ptr<GameWorldController> gameWorldController;
    std::shared_ptr<QThread> mainThread;
    std::shared_ptr<Queue<core::Command>> commandQueue;
};

}  // namespace server

#endif  // ENGINE_H
