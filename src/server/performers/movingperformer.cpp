#include "movingperformer.h"

#include <cmath>

#include <QDebug>

void
server::moving_performer::move(const std::shared_ptr<core::Object>& object, int64_t timeDelta,
                               const core::Moving& moving) {
    object->setRotationAngle(std::atan2(moving.getDirection().y(), moving.getDirection().x()));
    object->setPosition(getNextPosition(object, timeDelta, moving));
}

void
server::moving_performer::moveIfNoObstacles(const std::shared_ptr<core::Object>& object,
                                            int64_t timeDelta,
                                            const std::shared_ptr<core::GameWorld>& gameWorld,
                                            const std::shared_ptr<core::Moving>& moving) {
    if (!isObstacles(object, timeDelta, gameWorld, moving)) {
        server::moving_performer::move(object, timeDelta, *moving);
    }
}

bool server::moving_performer::isObstacles(const std::shared_ptr<core::Object>& object,
                                           int64_t timeDelta,
                                           const std::shared_ptr<core::GameWorld>& gameWorld,
                                           const std::shared_ptr<core::Moving>& moving) {
    QPolygonF objectPolygon = object->getRotatedHitbox();
    objectPolygon.translate(getNextPosition(object, timeDelta, *moving));
    for (const std::shared_ptr<core::Object>& otherObject : gameWorld->getObjects()) {
        if (otherObject->getId() == object->getId()) {
            continue;
        }
        if (otherObject->isIntersect(objectPolygon)) {
            return true;
        }
    }
    return false;
}

QPointF server::moving_performer::getNextPosition(const std::shared_ptr<core::Object>& object,
                                                  int64_t timeDelta, const core::Moving& moving) {
    return object->getPosition() +
           (moving.getDirection() *
            static_cast<float>(moving.getSpeed() * timeDelta / 1000)).toPointF();
}
