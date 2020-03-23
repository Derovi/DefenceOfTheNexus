//
// Created by derovi on 3/23/2020.
//

#ifndef CONTROLLER_H
#define CONTROLLER_H

namespace server {

class GameWorld;

class Controller {
  public:
    virtual void tick(GameWorld * world) = 0;
};

}


#endif //CONTROLLER_H
