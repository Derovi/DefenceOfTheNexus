#include <QDebug>
#include <QVector>
#include <QHash>
#include "../../core/gameworld.h"
#include "../../core/object.h"

#include "controller.h"
#include "gameworldcontroller.h"

// todo one controller for one object type

server::GameWorldController::GameWorldController(core::GameWorld* gameWorld): gameWorld(gameWorld) {
    for (core::Object* object : gameWorld->getObjects()) {
        controllers[object->getId()] = new Controller(object);
    }
}

void server::GameWorldController::tick(double deltaTime) {
    for (core::Object* object : gameWorld->getObjects()) {
        if (!controllers.contains(object->getId())) {
            controllers.insert(object->getId(), new Controller(object));
        }
    }

    QVector<int> eraseList;

    for (auto iterator = controllers.begin(); iterator != controllers.end(); ++iterator) {
        if (iterator.value()->getObject() == nullptr) {
            eraseList.push_back(iterator.key());
        } else {
            iterator.value()->tick(gameWorld, deltaTime);
        }
    }

    for (int id : eraseList) {
        controllers.remove(id);
    }
}

core::GameWorld* server::GameWorldController::getGameWorld() {
    return gameWorld;
}

void server::GameWorldController::setGameWorld(core::GameWorld* gameWorld) {
    GameWorldController::gameWorld = gameWorld;
}

void server::GameWorldController::addObject(core::Object* object) {
    gameWorld->getObjects()[object->getId()] = object;
    controllers[object->getId()] = new Controller(object);
}

void server::GameWorldController::removeObject(int64_t id) {
    if (!gameWorld->getObjects().contains(id)) {
        return;
    }
    delete gameWorld->getObjects()[id];
    gameWorld->getObjects().remove(id);
    delete controllers[id];
    controllers.remove(id);
}

server::GameWorldController::~GameWorldController() {
    for (Controller*& controller : controllers.values()) {
        delete controller;
    }
}
