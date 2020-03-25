#ifndef UNITCONTROLLER_H
#define UNITCONTROLLER_H

#include "../core/unit.h"

#include "controller.h"

namespace server {

class UnitController : public Controller {
  public:
    explicit UnitController(::core::Unit* unit);

    UnitController();

    static bool create(Controller*& controller, core::Object* object);

    void tick(core::GameWorld* world, double timeDelta) override;

    ::core::Unit* getUnit() const;

    void setUnit(::core::Unit* unit);

  private:

    ::core::Unit* unit;
};

}


#endif //UNITCONTROLLER_H
