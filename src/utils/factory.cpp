#include <QDebug>

#include "factory.h"

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

QHash<QString, std::function<server::Strategy*(core::Object*,
                                               server::DataBundle&)>> utils::Factory::strategyCreators;