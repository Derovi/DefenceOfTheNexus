#include <QDebug>

#include "../core/gameworld.h"
#include "../core/object.h"

#include "gameworldcontroller.h"

// todo one controller for one object type

server::GameWorldController::GameWorldController(core::GameWorld* gameWorld): gameWorld(gameWorld) {
    for (core::Object* object : gameWorld->getObjects()) {
        controllers[object->getId()] = Controller::getController(object);
    }
}

void server::GameWorldController::tick(double deltaTime) {
    for (Controller* controller : controllers) {
        controller->tick(gameWorld, deltaTime);
    }
}

core::GameWorld* server::GameWorldController::getGameWorld() const {
    return gameWorld;
}

void server::GameWorldController::setGameWorld(core::GameWorld* gameWorld) {
    GameWorldController::gameWorld = gameWorld;
}

void server::GameWorldController::addObject(core::Object* object) {
    gameWorld->getObjects()[object->getId()] = object;
    controllers[object->getId()] = Controller::getController(object);
}

void server::GameWorldController::removeObject(qint64 id) {
    if (!gameWorld->getObjects().contains(id)) {
        return;
    }
    delete gameWorld->getObjects()[id];
    gameWorld->getObjects().remove(id);
    delete controllers[id];
    controllers.remove(id);
}

