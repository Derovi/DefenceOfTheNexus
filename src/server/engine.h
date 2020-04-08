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

    core::GameWorld* getGameWorld();

    GameWorldController* getGameWorldController();

    const GameConfiguration& getGameConfiguration() const;

    QThread* getMainThread() const;

    QQueue<core::Command>* getCommandQueue() const;

    void finish();

    bool isFinished() const;

    ~Engine();

  private:
    core::GameWorld* gameWorld;
    GameWorldController* gameWorldController;
    CommandExecutor commandExecutor;
    GameConfiguration gameConfiguration;
    QThread* mainThread;
    std::atomic<bool> finished;

    // todo fix race-condition
    QQueue<core::Command>* commandQueue;

    void executeCommands();
};

}

#endif //ENGINE_H