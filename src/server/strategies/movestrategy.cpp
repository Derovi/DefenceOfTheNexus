#include "../performers/movingperformer.h"
#include "movestrategy.h"

void server::MoveStrategy::tick(core::GameWorld* world, double timeDelta) {
    moving_performer::move(getObject(), timeDelta, *moving);
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

