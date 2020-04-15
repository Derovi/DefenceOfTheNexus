#include "movingperformer.h"

void
server::moving_performer::move(std::shared_ptr<core::Object> object, double timeDelta,
                               const core::Moving& moving) {
    object->setPosition(getNextPosition(object, timeDelta, moving));
}

void
server::moving_performer::moveIfNoObstacles(std::shared_ptr<core::Object> object, double timeDelta,
                                            std::shared_ptr<core::GameWorld> gameWorld,
                                            std::shared_ptr<core::Moving> moving) {
    bool isOk = true;

    QPolygonF hitbox = object->getHitbox();

    QPointF nextPosition = server::moving_performer::getNextPosition(object, timeDelta, *moving);
    for (auto& i:hitbox) {
        i += nextPosition;
    }

    for (auto obj:gameWorld->getObjects()) {
        QPolygonF gameObject = obj->getHitbox();
        for (auto& j : gameObject) {
            j += obj->getPosition();
        }
        if (!gameObject.intersects(hitbox)) {
            isOk = false;
            break;
        }
    }
    if (isOk) {
        object->setPosition(nextPosition);
    }
}

QPointF server::moving_performer::getNextPosition(std::shared_ptr<core::Object> object,
                                                  double timeDelta, const core::Moving& moving) {
    return object->getPosition() +
           (moving.getDirection() * static_cast<float>(moving.getSpeed() * timeDelta)).toPointF();
}
