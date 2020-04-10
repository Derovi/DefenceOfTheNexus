#include "../performers/movingperformer.h"
#include "movestrategy.h"

void server::MoveStrategy::tick(core::GameWorld* world, double timeDelta) {
//    MovingPerformer movingPerformer(world, getObject(), timeDelta);
//    movingPerformer.move();
}

QString server::MoveStrategy::getName() {
    return name;
}

QString server::MoveStrategy::name = "moveStrategy";

server::MoveStrategy::MoveStrategy(core::Object* object, server::DataBundle& dataBundle):
        Strategy(object) {
    assign(dataBundle);
}

void server::MoveStrategy::assign(server::DataBundle& dataBundle) {
    dataBundle.assign("moving", moving);
}

server::MoveStrategy::~MoveStrategy() = default;

