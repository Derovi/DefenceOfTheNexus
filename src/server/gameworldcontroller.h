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

  private:

    core::GameWorld* gameWorld;

    QVector<Controller*> controllers;
};

}


#endif //GAMEWORLDCONTROLLER_H
