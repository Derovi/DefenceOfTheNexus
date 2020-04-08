#include "../../core/unit.h"

#include "../performers/movingperformer.h"
#include "unitcontroller.h"

void server::UnitController::tick(core::GameWorld* world, double timeDelta) {
    // todo change class to namespace
    MovingPerformer movingPerformer(world, unit, timeDelta);
    movingPerformer.move();

}

server::UnitController::UnitController(::core::Unit* unit): unit(unit) {
}

bool server::UnitController::create(server::Controller*& controller, core::Object* object) {
    auto* unit = dynamic_cast<core::Unit*>(object);
    if (unit) {
        controller = new UnitController(unit);
        return true;
    }
    return false;
}

core::Unit* server::UnitController::getUnit() const {
    return unit;
}

void server::UnitController::setUnit(core::Unit* unit) {
    UnitController::unit = unit;
}
