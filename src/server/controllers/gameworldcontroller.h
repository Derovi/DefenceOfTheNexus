#ifndef GAMEWORLDCONTROLLER_H
#define GAMEWORLDCONTROLLER_H

#include <QVector>

#include "../../core/gameworld.h"

#include "controller.h"

namespace server {

class GameWorldController {

  public:
    explicit GameWorldController(std::shared_ptr<core::GameWorld> gameWorld);

    void tick(double deltaTime);

    std::shared_ptr<core::GameWorld> getGameWorld();

    void setGameWorld(std::shared_ptr<core::GameWorld> gameWorld);

    void addObject(std::shared_ptr<core::Object> object);

    void removeObject(int64_t id);

    ~GameWorldController() = default;

  private:

    std::shared_ptr<core::GameWorld> gameWorld;

    // id, controller
    QHash<int64_t, std::shared_ptr<Controller>> controllers;
};

}

#endif //GAMEWORLDCONTROLLER_H
