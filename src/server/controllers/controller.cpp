#include <QDebug>

#include "../../utils/factory.h"

#include "controller.h"
#include "unitcontroller.h"
#include "databundle.h"

server::Controller* server::Controller::createController(core::Object* object) {
    return utils::Factory::createController(object);
}

const QHash<QString, server::Strategy*>& server::Controller::getStrategies() const {
    return strategies;
}

void server::Controller::addStrategy(const QString& strategyName) {
    addStrategies({QStringList(strategyName)});
}

void server::Controller::removeStrategy(const QString& strategyName) {
    removeStrategies({QStringList(strategyName)});
}

void server::Controller::resumeStrategy(const QString& strategyName) {
    resumeStrategies({QStringList(strategyName)});
}

void server::Controller::pauseStrategy(const QString& strategyName) {
    pauseStrategies({QStringList(strategyName)});
}

void server::Controller::addStrategies(const QStringList& strategyNames) {
    DataBundle dataBundle = createDataBundle();
    for (Strategy* strategy : strategies) {
        strategy->assign(dataBundle);
    }
    for (const QString& strategyName : strategyNames) {
        if (strategies.contains(strategyName)) {
            continue;
        }
        Strategy* strategy = utils::Factory::createStrategy(strategyName, getObject(), dataBundle);
        if (strategy) {
            strategies.insert(strategyName, strategy);
        }
    }
}

void server::Controller::removeStrategies(const QStringList& strategyNames) {
    for (const QString& strategyName : strategyNames) {
        if (!strategies.contains(strategyName)) {
            continue;
        }
        delete strategies[strategyName];
        strategies.remove(strategyName);
    }
}

void server::Controller::resumeStrategies(const QStringList& strategyNames) {
    for (const QString& strategyName : strategyNames) {
        if (!strategies.contains(strategyName)) {
            continue;
        }
        strategies[strategyName]->pause();
    }
}

void server::Controller::pauseStrategies(const QStringList& strategyNames) {
    for (const QString& strategyName : strategyNames) {
        if (!strategies.contains(strategyName)) {
            continue;
        }
        strategies[strategyName]->resume();
    }
}
