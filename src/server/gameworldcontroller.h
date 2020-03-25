//
// Created by derovi on 3/23/2020.
//

#ifndef GAMEWORLDCONTROLLER_H
#define GAMEWORLDCONTROLLER_H


#include "../core/gameworld.h"
#include "controller.h"
#include <QVector>

namespace server {

class GameWorldController {

  public:
    explicit GameWorldController(core::GameWorld * gameWorld);

    void tick(double deltaTime);

    core::GameWorld* getGameWorld() const;

    void setGameWorld(core::GameWorld* gameWorld);

  private:

    core::GameWorld * gameWorld;

    QVector<Controller *> controllers;
};

}


#endif //GAMEWORLDCONTROLLER_H
