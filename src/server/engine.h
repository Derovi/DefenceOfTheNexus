#ifndef ENGINE_H
#define ENGINE_H

#include <QThread>

#include "../utils/queue.h"
#include "../core/gameworld.h"
#include "../core/command.h"
#include "controllers/gameworldcontroller.h"

#include "gameconfiguration.h"
#include "commandexecutor.h"
#include "../core/event.h"
#include "aiplayer.h"

namespace server {

class Engine : public QObject {
    Q_OBJECT

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

    const std::shared_ptr<core::GameWorld>& getWorldBeforeUpdate() const;

    void generateEvent(const core::Event& event);

    void finish();

    void addAIPlayer(const std::shared_ptr<AIPlayer>& aiPlayer);

    bool isFinished() const;

  private:
    void executeCommands();

    CommandExecutor commandExecutor;
    GameConfiguration gameConfiguration;
    QVector<core::Event> events;
    QVector<std::shared_ptr<AIPlayer>> aiPlayers;
    std::atomic_bool finished;
    std::shared_ptr<core::GameWorld> gameWorld;
    std::shared_ptr<core::GameWorld> worldBeforeUpdate;
    std::shared_ptr<GameWorldController> gameWorldController;
    std::shared_ptr<QThread> mainThread;
    std::shared_ptr<Queue<core::Command>> commandQueue;

  signals:
    void updated(QVector<core::Event> events);
};

}  // namespace server

#endif  // ENGINE_H
