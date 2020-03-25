//
// Created by derovi on 3/23/2020.
//

#ifndef MOVINGPERFORMER_H
#define MOVINGPERFORMER_H

#include "../core/gameworld.h"
#include "../core/object.h"
#include "../core/moving.h"
#include <QPointF>
#include <QVector2D>

namespace server {

template <class T>
class MovingPerformer {
  public:
    MovingPerformer(core::GameWorld * gameWorld, T * object, double timeDelta) :
                                gameWorld(gameWorld), object(object), timeDelta(timeDelta)  {}

    void move() {
        object->setPosition(getNextPosition());
    }

    void moveIfNoObstacles() {

    }

    QPointF getNextPosition() {
        double newX = object->getPosition().x() + object->getDirection().normalized().x() *
                object->getSpeed() * timeDelta;
        double newY = object->getPosition().y() + object->getDirection().normalized().y() *
                object->getSpeed() * timeDelta;
        return QPointF(newX, newY);
    }

  private:

    core::GameWorld* gameWorld;
    T* object;
    double timeDelta;

};

}


#endif //MOVINGPERFORMER_H
