#include "movingperformer.h"

void
server::moving_performer::move(core::Object* object, double timeDelta, const core::Moving& moving) {
    object->setPosition(getNextPosition(object, timeDelta, moving));
}

// todo moveIfNoObstacles function
void server::moving_performer::moveIfNoObstacles(core::Object* object, double timeDelta,
                                                 core::GameWorld* gameWorld,
                                                 core::Moving* moving) {}

QPointF server::moving_performer::getNextPosition(core::Object* object, double timeDelta,
                                                  const core::Moving& moving) {
    double newX = object->getPosition().x() + moving.getDirection().x() *
                                              moving.getSpeed() * timeDelta;
    double newY = object->getPosition().y() + moving.getDirection().y() *
                                              moving.getSpeed() * timeDelta;
    return QPointF(newX, newY);
}
