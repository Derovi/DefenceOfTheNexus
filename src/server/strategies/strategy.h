#ifndef STRATEGY_H
#define STRATEGY_H

#include <QString>

#include "../../core/object.h"
#include "../controllers/databundle.h"
#include "../../core/gameworld.h"

namespace server {

class Strategy {
  public:
    Strategy() = default;

    virtual void tick(core::GameWorld* world, double timeDelta) = 0;

    virtual QString getName() = 0;

    core::Object* getObject() const;

    bool isPaused() const;

    void setPaused(bool paused);

  private:

    core::Object* object;

    bool paused = false;
};

}

#endif //STRATEGY_H
