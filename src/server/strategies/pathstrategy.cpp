#include "pathstrategy.h"

#include <cmath>

#include <QDebug>
#include <QtGlobal>
#include <QLineF>

#include "../performers/movingperformer.h"

namespace server {

PathStrategy::PathStrategy(std::shared_ptr<core::Object> object):
        Strategy(object), moving(nullptr), destPoint(nullptr) {}

QString PathStrategy::getName() {
    return name;
}

void PathStrategy::assign(DataBundle& dataBundle) {
    dataBundle.assign("moving", moving);
    dataBundle.assign("destinationPoint", destPoint);
}

void PathStrategy::cancelTargets() {
    destPoint = nullptr;
}

void PathStrategy::tick(std::shared_ptr<core::GameWorld> world, double timeDelta) {
    if (destPoint == nullptr) {
        return;
    }
    qDebug() << *destPoint;
    if (qFuzzyIsNull(moving->getSpeed())) {
        moving->setDirection(QVector2D(0, 0));
        return;
    }
    if (QLineF(*destPoint, getObject()->getPosition()).length() <
        timeDelta / 1000.0 * moving->getSpeed()) {
        moving->setDirection(QVector2D(0, 0));
        return;
    }
    QVector2D direction(*destPoint - getObject()->getPosition());
    direction.normalize();

    static const auto rotateCounterClockwise = [](const QVector2D& v) {
        return QVector2D(v.x() * M_SQRT1_2 - v.y() * M_SQRT1_2,
                v.x() * M_SQRT1_2 + v.y() * M_SQRT1_2).normalized();
    };

    static const auto rotateClockwise = [](const QVector2D& v) {
        return QVector2D(v.x() * M_SQRT1_2 + v.y() * M_SQRT1_2,
                -v.x() * M_SQRT1_2 + v.y() * M_SQRT1_2).normalized();
    };

    const auto isVisited = [&]() {
        return false;
//        for (const QPointF& pt : path) {
//            double distance = QLineF(pt, moving_performer::getNextPosition(getObject(),
//                                                                           timeDelta,
//                                                                           *moving)).length();
//            if (distance < 1000.0 / timeDelta *  moving->getSpeed()) {
//                return true;
//            }
//        }
//        return false;
    };


    if (!path.empty()) {
        auto currentDirection = moving->getDirection();
        for (int it = 0; it < 8; ++it) {
            currentDirection = rotateCounterClockwise(currentDirection);
            moving->setDirection(currentDirection);
            if (moving_performer::isObstacles(getObject(), timeDelta, world, moving)
                || isVisited()) {
                break;
            }
            if (std::abs(direction.x() - currentDirection.x()) < 0.3
                && std::abs(direction.y() - currentDirection.y()) < 0.3) {
                break;
            }
        }
        if (!moving_performer::isObstacles(getObject(), timeDelta, world, moving)
            && !isVisited()) {
            path.clear();
            return;
        }
        direction = currentDirection;
    }
    for (int it = 0; it < 8; ++it) {
        moving->setDirection(direction);
        if (!moving_performer::isObstacles(getObject(), timeDelta, world, moving)) {
            return;
        }
        if (it == 0) {
            path.append(getObject()->getPosition());
            if (path.size() > 10) {
                path.pop_front();
            }
        }
        direction = rotateClockwise(direction);
    }
    moving->setDirection(QVector2D(0, 0));
}

}  // namespace server
