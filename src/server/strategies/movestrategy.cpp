#include "movestrategy.h"

#include <cmath>

#include "../performers/movingperformer.h"

void server::MoveStrategy::tick(std::shared_ptr<core::GameWorld> world, int timeDelta) {
    if (moving != nullptr) {
        moving_performer::moveIfNoObstacles(getObject(), timeDelta, world, moving);
        auto direction = moving->getDirection().normalized();
//        if (!qFuzzyIsNull(direction.x()) && !qFuzzyIsNull(direction.y())) {
//            getObject()->setRotationAngle(std::atan2(direction.y(), direction.x()));
//        }
    }
}

QString server::MoveStrategy::getName() {
    return name;
}

server::MoveStrategy::MoveStrategy(std::shared_ptr<core::Object> object): Strategy(object) {}

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
