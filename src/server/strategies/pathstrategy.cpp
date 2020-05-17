#include "pathstrategy.h"

#include <cmath>

#include <QDebug>
#include <QtGlobal>
#include <QLineF>

#include "../performers/movingperformer.h"

namespace server {

PathStrategy::PathStrategy(std::shared_ptr<core::Object> object):
    Strategy(object), isRounding(false), roundingStyle(kClockwise), moving(nullptr),
    destPoint(nullptr), destIntersectionUpdate(0) {}

QString PathStrategy::getName() {
    return name;
}

void PathStrategy::assign(DataBundle& dataBundle) {
    dataBundle.assign("moving", moving);
    dataBundle.assign("destinationPoint", destPoint);
}

void PathStrategy::cancelTargets() {
    destPoint = nullptr;
    isRounding = false;
    roundingStyle = static_cast<RoundingStyle>(roundingStyle ^ 1);
}

void PathStrategy::tick(std::shared_ptr<core::GameWorld> world, int timeDelta) {
    if (destPoint == nullptr) {
        moving->setSpeed(0);
        return;
    } else {
        moving->setSpeed(moving->getMaxSpeed());
    }
    if (qFuzzyIsNull(moving->getSpeed())) {
        moving->setDirection(QVector2D(0, 0));
        return;
    }
    if (QLineF(*destPoint, getObject()->getPosition()).length() <
        timeDelta / 1000.0 * moving->getSpeed()) {
        destPoint = nullptr;
        return;
    }

    QVector2D direction(*destPoint - getObject()->getPosition());
    direction.normalize();

    destIntersectionUpdate += timeDelta;
    if (destIntersectionUpdate > 100) {
        destIntersectionUpdate = 0;
        auto targetObject = world->objectAt(*destPoint);
        if (targetObject != nullptr) {
            auto directMoving = std::static_pointer_cast<core::Moving>(moving->clone());

            auto hitboxOnMap = getObject()->getRotatedHitbox();
            hitboxOnMap.translate(moving_performer::getNextPosition(getObject(),
                                                                    timeDelta, *directMoving));

            if (targetObject->isIntersect(hitboxOnMap)) {
                destPoint = nullptr;
                moving->setDirection(direction);
                return;
            }
        }
    }

    static const auto rotateCounterClockwise = [](const QVector2D& v, double angle = M_PI_4 / 2) {
        return QVector2D(v.x() * std::cos(angle) - v.y() * std::sin(angle),
                         v.x() * std::sin(angle) + v.y() * std::cos(angle)).normalized();
    };

    static const auto rotateClockwise = [](const QVector2D& v, double angle = M_PI_4 / 2) {
        return rotateCounterClockwise(v, M_2_PI - angle);
    };

    static const auto rotate = [](const QVector2D& v, RoundingStyle style) {
        return (style == kCounterClockwise ? rotateCounterClockwise(v) : rotateClockwise(v));
    };
    if (isRounding) {
        auto currentDirection = moving->getDirection();
        for (int it = 0; it < 16; ++it) {
            currentDirection = rotate(currentDirection, static_cast<RoundingStyle>(!roundingStyle));
            moving->setDirection(currentDirection);
            if (moving_performer::isObstacles(getObject(), timeDelta, world, moving)) {
                break;
            }
            if (std::abs(direction.x() - currentDirection.x()) < 0.3
                && std::abs(direction.y() - currentDirection.y()) < 0.3) {
                break;
            }
        }
        if (!moving_performer::isObstacles(getObject(), timeDelta, world, moving)) {
            isRounding = false;
            return;
        }
        direction = currentDirection;
    }
    for (int it = 0; it < 16; ++it) {
        moving->setDirection(direction);
        if (!moving_performer::isObstacles(getObject(), timeDelta, world, moving)) {
            return;
        }
        isRounding = true;
        direction = rotate(direction, roundingStyle);
    }
    moving->setDirection(QVector2D(0, 0));
}

}  // namespace server
