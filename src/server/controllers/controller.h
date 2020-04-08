#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../../core/gameworld.h"
#include "../../core/object.h"

namespace server {

class Controller {
  public:
    virtual void tick(core::GameWorld* world, double timeDelta) = 0;

    static Controller* createController(core::Object* object);

    virtual ~Controller() = default;
};

}


#endif //CONTROLLER_H
