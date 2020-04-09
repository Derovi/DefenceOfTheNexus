#include <QDebug>

#include "../../utils/factory.h"

#include "controller.h"
#include "unitcontroller.h"

server::Controller* server::Controller::createController(core::Object* object) {
    return utils::Factory::createController(object);
}

