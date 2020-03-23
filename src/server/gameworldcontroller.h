//
// Created by derovi on 3/23/2020.
//

#ifndef GAMEWORLDCONTROLLER_H
#define GAMEWORLDCONTROLLER_H


#include "../core/gameworld.h"
#include "controller.h"

namespace server {

class GameWorldController : core::GameWorld {
  public:
    GameWorldController(GameWorld &gameWorld);

    void tick();
};

}


#endif //GAMEWORLDCONTROLLER_H
