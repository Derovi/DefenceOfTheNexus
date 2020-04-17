#include "../performers/movingperformer.h"
#include "movestrategy.h"

void server::MoveStrategy::tick(std::shared_ptr<core::GameWorld> world, double timeDelta) {
    moving_performer::moveIfNoObstacles(getObject(), timeDelta, world, moving);
}

QString server::MoveStrategy::getName() {
    return name;
}

server::MoveStrategy::MoveStrategy(std::shared_ptr<core::Object> object) : Strategy(object) {}

void server::MoveStrategy::assign(server::DataBundle& dataBundle) {
    dataBundle.assign("moving", moving);
}

QStringList server::MoveStrategy::getRequiredAttributes() {
    return requiredAttributes;
}

QStringList server::MoveStrategy::getStartAfter() {
    return startAfter;
}

QString server::MoveStrategy::name = "moveStrategy";

const QStringList server::MoveStrategy::requiredAttributes = {"moving"};

const QStringList server::MoveStrategy::startAfter = {};
