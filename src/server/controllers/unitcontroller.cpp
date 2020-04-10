#include "../../core/unit.h"

#include "../performers/movingperformer.h"
#include "unitcontroller.h"

server::UnitController::UnitController(core::Unit* unit) : unit(unit) {}

void server::UnitController::tick(core::GameWorld* world, double timeDelta) {
    // todo change class to namespace
    MovingPerformer movingPerformer(world, unit, timeDelta);
    movingPerformer.move();

}

server::Controller* server::UnitController::create(core::Object* object) {
    auto* unit = dynamic_cast<core::Unit*>(object);
    if (unit) {
        return new UnitController(unit);
    }
    return nullptr;
}

core::Unit* server::UnitController::getUnit() const {
    return unit;
}

void server::UnitController::setUnit(core::Unit* unit) {
    UnitController::unit = unit;
}

core::Object* server::UnitController::getObject() {
    return unit;
}

server::DataBundle server::UnitController::createDataBundle() {
    DataBundle dataBundle;
    //dataBundle.registerVariable("moving", &moving);
    return dataBundle;
}
