#include "movingperformer.h"

void
server::moving_performer::move(core::Object* object, double timeDelta, const core::Moving& moving) {
    object->setPosition(getNextPosition(object, timeDelta, moving));
}

void server::moving_performer::moveIfNoObstacles(core::Object* object, double timeDelta,
                                                 core::GameWorld* gameWorld,
                                                 core::Moving* moving) {
    bool isOk = true;

    QPolygonF hitbox = object->getHitbox();

    QPointF nextPosition = server::moving_performer::getNextPosition(object, timeDelta, *moving);
    for (auto& i:hitbox) {
        i.setX(i.x() + nextPosition.x());
        i.setY(i.y() + nextPosition.y());
    }

    for (auto i:gameWorld->getObjects()) {
        QPolygonF gameObject = i->getHitbox();
        for (auto& j : gameObject) {
            j.setX(j.x() + i->getPosition().x());
            j.setY(j.y() + i->getPosition().y());
        }
        if (!gameObject.intersected(hitbox).isEmpty()) {
            isOk = false;
            break;
        }
    }
    if (isOk) {
        object->setPosition(nextPosition);
    }
}

QPointF server::moving_performer::getNextPosition(core::Object* object, double timeDelta,
                                                  const core::Moving& moving) {
    double newX = object->getPosition().x() + moving.getDirection().x() *
                                              moving.getSpeed() * timeDelta;
    double newY = object->getPosition().y() + moving.getDirection().y() *
                                              moving.getSpeed() * timeDelta;
    return QPointF(newX, newY);
}
