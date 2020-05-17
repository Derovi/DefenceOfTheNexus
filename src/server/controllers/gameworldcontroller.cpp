#include <QDebug>
#include <QVector>

#include "../../core/gameworld.h"
#include "../../core/object.h"

#include "controller.h"
#include "gameworldcontroller.h"
#include "../engine.h"

// todo one controller for one object type

server::GameWorldController::GameWorldController(std::shared_ptr<core::GameWorld> gameWorld,
                                                 Engine* engine):
        gameWorld(gameWorld), engine(engine) {
    for (std::shared_ptr<core::Object> object : gameWorld->getObjects()) {
        controllers[object->getId()] = std::shared_ptr<Controller>(new Controller(object));
    }
}

void server::GameWorldController::tick(int deltaTime) {
    for (std::shared_ptr<core::Object> object : gameWorld->getObjects()) {
        if (!controllers.contains(object->getId())) {
            controllers.insert(object->getId(),
                               std::shared_ptr<Controller>(new Controller(object)));
        }
    }

    QVector<int> eraseList;

    for (auto iterator = controllers.begin();
         iterator != controllers.end();
         ++iterator) {
        if (!gameWorld->getObjects().contains(iterator.key())) {
            eraseList.push_back(iterator.key());
        } else {
            iterator.value()->tick(gameWorld, deltaTime);
        }
    }

    for (int id : eraseList) {
        controllers.remove(id);
    }

    for (const core::Event& event : gameWorld->getGeneratedEvent()) {
        engine->generateEvent(event);
    }
    gameWorld->clearEvents();
}

std::shared_ptr<core::GameWorld> server::GameWorldController::getGameWorld() {
    return gameWorld;
}

void server::GameWorldController::setGameWorld(std::shared_ptr<core::GameWorld> gameWorld) {
    GameWorldController::gameWorld = gameWorld;
}

void server::GameWorldController::addObject(std::shared_ptr<core::Object> object) {
    gameWorld->getObjects()[object->getId()] = object;
    controllers[object->getId()] = std::shared_ptr<Controller>(new Controller(object));
}

void server::GameWorldController::removeObject(int64_t id) {
    if (!gameWorld->getObjects().contains(id)) {
        return;
    }
    gameWorld->getObjects().remove(id);
    controllers.remove(id);
}

const QHash<int64_t, std::shared_ptr<server::Controller>>&
server::GameWorldController::getControllers() {
    return controllers;
}
