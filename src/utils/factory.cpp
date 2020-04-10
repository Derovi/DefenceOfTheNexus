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

server::Strategy*
utils::Factory::createStrategy(const QString& strategyName, core::Object* object,
                               server::DataBundle& dataBundle) {
    if (object == nullptr || !strategyCreators.contains(strategyName)) {
        return nullptr;
    }
    return strategyCreators[strategyName](object, dataBundle);
}

void utils::Factory::registerStrategy(const QString& strategyName, std::function<server::Strategy*(
        core::Object*, server::DataBundle&)> creator) {
    strategyCreators.insert(strategyName, creator);
}

QHash<QString, std::function<server::Controller*(
        core::Object*)>> utils::Factory::controllerCreators;
