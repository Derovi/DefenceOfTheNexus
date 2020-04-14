#include "movingperformer.h"

void server::moving_performer::move(std::shared_ptr<core::Object> object, double timeDelta,
                                    const core::Moving& moving) {
    object->setPosition(getNextPosition(object, timeDelta, moving));
}

// todo moveIfNoObstacles function
void server::moving_performer::moveIfNoObstacles(
        std::shared_ptr<core::Object> object, double timeDelta,
        std::shared_ptr<core::GameWorld> gameWorld,
        std::shared_ptr<core::Moving> moving) {}

QPointF server::moving_performer::getNextPosition(std::shared_ptr<core::Object> object,
                                                  double timeDelta, const core::Moving& moving) {
    double newX = object->getPosition().x() + moving.getDirection().x() *
                                              moving.getSpeed() * timeDelta;
    double newY = object->getPosition().y() + moving.getDirection().y() *
                                              moving.getSpeed() * timeDelta;
    return QPointF(newX, newY);
}
