#ifndef GAMEWORLDCONTROLLER_H
#define GAMEWORLDCONTROLLER_H

#include <QVector>

#include "../../core/gameworld.h"

#include "controller.h"

namespace server {

class Engine;

class GameWorldController {

  public:
    GameWorldController(std::shared_ptr<core::GameWorld> gameWorld, Engine* engine);

    void tick(int deltaTime);

    std::shared_ptr<core::GameWorld> getGameWorld();

    void setGameWorld(std::shared_ptr<core::GameWorld> gameWorld);

    void addObject(std::shared_ptr<core::Object> object);

    void removeObject(int64_t id);

    const QHash<int64_t, std::shared_ptr<Controller>>& getControllers();

    ~GameWorldController() = default;

  private:

    std::shared_ptr<core::GameWorld> gameWorld;

    // id, controller
    QHash<int64_t, std::shared_ptr<Controller>> controllers;

    Engine* engine;
};

}

#endif //GAMEWORLDCONTROLLER_H
