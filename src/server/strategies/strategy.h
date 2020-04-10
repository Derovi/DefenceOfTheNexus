#ifndef STRATEGY_H
#define STRATEGY_H

#include <QString>

#include "../../core/object.h"
#include "../controllers/databundle.h"
#include "../../core/gameworld.h"

namespace server {

class Strategy {
  public:
    explicit Strategy(core::Object*);

    virtual ~Strategy() = 0;

    virtual void tick(core::GameWorld* world, double timeDelta) = 0;

    virtual QString getName() = 0;

    virtual void assign(DataBundle& dataBundle) = 0;

    core::Object* getObject() const;

    bool isPaused() const;

    virtual void pause();

    virtual void resume();

  private:

    core::Object* object;

    bool paused = false;
};

}

#endif //STRATEGY_H
