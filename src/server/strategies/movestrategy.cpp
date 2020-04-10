#include "../performers/movingperformer.h"
#include "movestrategy.h"

void server::MoveStrategy::tick(core::GameWorld* world, double timeDelta) {
    moving_performer::move(getObject(), timeDelta, *moving);
}

QString server::MoveStrategy::getName() {
    return name;
}

server::MoveStrategy::MoveStrategy(core::Object* object) : Strategy(object) {}

void server::MoveStrategy::assign(server::DataBundle& dataBundle) {
    dataBundle.assign("moving", moving);
}

QStringList server::MoveStrategy::getRequiredAttributes() {
    return requiredAttributes;
}

QStringList server::MoveStrategy::getStartAfter() {
    return startAfter;
}

server::MoveStrategy::~MoveStrategy() = default;

QString server::MoveStrategy::name = "moveStrategy";

const QStringList server::MoveStrategy::requiredAttributes = {"moving"};

const QStringList server::MoveStrategy::startAfter = {};



