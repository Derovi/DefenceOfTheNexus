#include <QDebug>

#include "../core/gameworld.h"
#include "../core/object.h"

#include "gameworldcontroller.h"

server::GameWorldController::GameWorldController(core::GameWorld* gameWorld): gameWorld(gameWorld) {
    for (core::Object* object : gameWorld->getObjects()) {
        controllers.push_back(Controller::getController(object));
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
