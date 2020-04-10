#include <QDebug>

#include "factory.h"

server::Strategy*
utils::Factory::createStrategy(const QString& strategyName, core::Object* object) {
    if (object == nullptr || !strategyCreators.contains(strategyName)) {
        return nullptr;
    }
    return strategyCreators[strategyName](object);
}

void utils::Factory::registerStrategy(const QString& strategyName, std::function<server::Strategy*(
        core::Object*)> creator) {
    strategyCreators.insert(strategyName, creator);
}

QHash<QString, std::function<server::Strategy*(core::Object*)>> utils::Factory::strategyCreators;