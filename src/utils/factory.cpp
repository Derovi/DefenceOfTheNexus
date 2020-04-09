#include <QDebug>

#include "factory.h"

server::Controller* utils::Factory::createController(core::Object* object) {
    if (object == nullptr || !controllerCreators.contains(object->getTypeName())) {
        return nullptr;
    }
    return controllerCreators[object->getTypeName()](object);
}

void utils::Factory::registerController(const QString& typeName,
                                        std::function<server::Controller*(core::Object*)> creator) {
    controllerCreators.insert(typeName, creator);
}

void utils::Factory::registerStrategy(const QString& strategyName, std::function<server::Strategy*(
        server::Controller*)> creator) {
    strategyCreators.insert(strategyName, creator);
}

QHash<QString, std::function<server::Controller*(core::Object*)>> utils::Factory::controllerCreators;
