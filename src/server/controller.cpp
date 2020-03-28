#include <QDebug>

#include "controller.h"
#include "unitcontroller.h"

server::Controller* server::Controller::getController(core::Object* object) {
    Controller* controller = nullptr;
    if (UnitController::create(controller, object)) {
        return controller;
    }
    return nullptr;
}

