#include <QDebug>

#include "movingperformer.h"

void
server::moving_performer::move(std::shared_ptr<core::Object> object, int timeDelta,
                               const core::Moving& moving) {
    object->setPosition(getNextPosition(object, timeDelta, moving));
}

void
server::moving_performer::moveIfNoObstacles(std::shared_ptr<core::Object> object, int timeDelta,
                                            std::shared_ptr<core::GameWorld> gameWorld,
                                            std::shared_ptr<core::Moving> moving) {
    if (!isObstacles(object, timeDelta, gameWorld, moving)) {
        server::moving_performer::move(object, timeDelta, *moving);
    }
}

bool server::moving_performer::isObstacles(std::shared_ptr<core::Object> object, int timeDelta,
                                           std::shared_ptr<core::GameWorld> gameWorld,
                                           std::shared_ptr<core::Moving> moving) {
    QPolygonF hitbox = object->getHitbox();

    QPointF nextPosition = server::moving_performer::getNextPosition(object, timeDelta, *moving);
    for (auto& vertex : hitbox) {
        vertex += nextPosition;
    }

    for (auto obj : gameWorld->getObjects()) {
        if (obj->getId() == object->getId()) {
            continue;
        }
        QPolygonF gameObject = obj->getHitbox();
        for (auto& vertex : gameObject) {
            vertex += obj->getPosition();
        }
        if (gameObject.intersects(hitbox)) {
            return true;
        }
    }
    return false;
}

QPointF server::moving_performer::getNextPosition(std::shared_ptr<core::Object> object,
                                                  int timeDelta, const core::Moving& moving) {
    return object->getPosition() + (moving.getDirection()
            * static_cast<float>(moving.getSpeed() * timeDelta / 1000.0)).toPointF();
}
