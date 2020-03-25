//
// Created by derovi on 3/23/2020.
//

#include <QMap>
#include <QDebug>
#include <QPointF>
#include "../core/gameworld.h"
#include "gameworldcontroller.h"
#include "../core/unit.h"

/*int main() {
    auto * gameWorld = new core::GameWorld();
    auto * unit = new core::Unit(0);
    unit->setPosition(QPointF(10, 10));
    unit->setSpeed(5);
    unit->setDirection(QVector2D(1, 1));
    gameWorld->getObjects().insert(0, unit);
    auto * worldController = new server::GameWorldController(gameWorld);
    worldController->tick(0.5);
    qDebug() << unit->getPosition().x() << ' ' << unit->getPosition().y();
}*/