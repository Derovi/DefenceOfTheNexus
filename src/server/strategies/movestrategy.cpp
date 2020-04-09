#include "../performers/movingperformer.h"
#include "movestrategy.h"

void server::MoveStrategy::tick(core::GameWorld* world, double timeDelta) {
    MovingPerformer movingPerformer(world, getObject(), timeDelta);
    movingPerformer.move();
}

QString server::MoveStrategy::getName() {
    return name;
}

QString server::MoveStrategy::name = "moveStrategy";

server::MoveStrategy::MoveStrategy(core::Object* object, server::DataBundle& dataBundle) {
    dataBundle.assign("direction", direction);
    dataBundle.assign("speed", speed);
    dataBundle.assign("maxSpeed", maxSpeed);
}
