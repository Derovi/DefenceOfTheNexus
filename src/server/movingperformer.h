#ifndef MOVINGPERFORMER_H
#define MOVINGPERFORMER_H

#include <QPointF>
#include <QVector2D>

#include "../core/gameworld.h"
#include "../core/object.h"
#include "../core/moving.h"

namespace server {

template<class T>
class MovingPerformer {
  public:
    MovingPerformer(core::GameWorld* gameWorld, T* object, double timeDelta);

    void move();

    void moveIfNoObstacles();

    QPointF getNextPosition();

  private:

    core::GameWorld* gameWorld;
    T* object;
    double timeDelta;
};

}

template<class T>
server::MovingPerformer<T>::MovingPerformer(core::GameWorld* gameWorld, T* object,
                                            double timeDelta) :
        gameWorld(gameWorld), object(object), timeDelta(timeDelta) {}

template<class T>
void server::MovingPerformer<T>::move() {
    object->setPosition(getNextPosition());
}

template<class T>
void server::MovingPerformer<T>::moveIfNoObstacles() {}

template<class T>
QPointF server::MovingPerformer<T>::getNextPosition()  {
    double newX = object->getPosition().x() + object->getDirection().x() *
                                              object->getSpeed() * timeDelta;
    double newY = object->getPosition().y() + object->getDirection().y() *
                                              object->getSpeed() * timeDelta;
    return QPointF(newX, newY);
}

#endif //MOVINGPERFORMER_H
