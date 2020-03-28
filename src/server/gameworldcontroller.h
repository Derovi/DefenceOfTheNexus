#ifndef GAMEWORLDCONTROLLER_H
#define GAMEWORLDCONTROLLER_H

#include <QVector>

#include "../core/gameworld.h"

#include "controller.h"

namespace server {

class GameWorldController {

  public:
    explicit GameWorldController(core::GameWorld* gameWorld);

    void tick(double deltaTime);

    core::GameWorld* getGameWorld() const;

    void setGameWorld(core::GameWorld* gameWorld);

    void addObject(core::Object* object);

    void removeObject(int64_t id);

  private:

    core::GameWorld* gameWorld;

    // id, controller
    QHash<int64_t, Controller*> controllers;
};

}

#endif //GAMEWORLDCONTROLLER_H
