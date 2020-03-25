//
// Created by derovi on 3/23/2020.
//

#include "movingperformer.h"
#include "unitcontroller.h"
#include "../core/unit.h"

void server::UnitController::tick(core::GameWorld* world, double timeDelta) {
    MovingPerformer movingPerformer(world, unit, timeDelta);
    movingPerformer.move();
}

server::UnitController::UnitController(::core::Unit * unit) : unit(unit) {
}

bool server::UnitController::create(server::Controller *& controller, core::Object* object) {
    auto * unit = dynamic_cast<::core::Unit *>(object);
    if (unit) {
        controller = new UnitController(unit);
        return true;
    }
    return false;
}

core::Unit* server::UnitController::getUnit() const {
    return unit;
}

void server::UnitController::setUnit(::core::Unit* unit) {
    UnitController::unit = unit;
}
