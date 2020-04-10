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

    ~Strategy();

    virtual void tick(core::GameWorld* world, double timeDelta) = 0;

    virtual QString getName() = 0;

    virtual QStringList getRequiredAttributes();

    virtual QStringList getStartAfter();

    virtual void assign(DataBundle& dataBundle) = 0;

    core::Object* getObject() const;

    bool isPaused() const;

  private:

    core::Object* object;
};

}

#endif //STRATEGY_H
