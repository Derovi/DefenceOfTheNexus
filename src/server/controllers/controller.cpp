#include <QDebug>
#include <QVector>

#include "../../utils/factory.h"

#include "controller.h"
#include "databundle.h"

server::Controller::Controller(core::Object* object): object(object) {
    addStrategies(object->getStrategies());
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
    prepare();
}

void server::Controller::removeStrategies(const QStringList& strategyNames) {
    for (const QString& strategyName : strategyNames) {
        if (!strategies.contains(strategyName)) {
            continue;
        }
        delete strategies[strategyName];
        strategies.remove(strategyName);
    }
    prepare();
}

core::Object* server::Controller::getObject() {
    return object;
}

void server::Controller::tick(core::GameWorld* world, double timeDelta) {
    for (Strategy* strategy : strategiesByPriority) {
        strategy->tick(world, timeDelta);
    }
}

server::DataBundle server::Controller::createDataBundle() {
    return server::DataBundle();
}

const QLinkedList<server::Strategy*>& server::Controller::getStrategiesByPriority() const {
    return strategiesByPriority;
}

void server::Controller::prepare() {
    strategiesByPriority.clear();
    QHash<QString, int> nameToVisitIteration;
    int currentIteration = 1;
    for (Strategy* strategy : strategies.values()) {
        if (nameToVisitIteration[strategy->getName()] == 0) {
            prepareStrategy(strategy, nameToVisitIteration, currentIteration++);
        }
    }
}

void server::Controller::prepareStrategy(server::Strategy* strategy,
                                        QHash<QString, int>& nameToVisitIteration,
                                        int currentIteration) {
    bool ok = true;
    for (const QString& attribute : strategy->getRequiredAttributes()) {
        if (!object->hasAttribute(attribute)) {
            ok = false;
            break;
        }
    }
    if (ok) {
        for (QString& needed : strategy->getStartAfter()) {
            if (!nameToVisitIteration.contains(needed)) {
                ok = false;
                break;
            }
            if (nameToVisitIteration[needed] == 0) {
                prepareStrategy(strategies[needed], nameToVisitIteration, currentIteration);
            }
            if (nameToVisitIteration[needed] != currentIteration) {
                ok = false;
                break;
            }
        }
    }
    if (ok) {
        strategiesByPriority.push_back(strategy);
        nameToVisitIteration[strategy->getName()] = currentIteration;
    } else {
        nameToVisitIteration[strategy->getName()] = -1;
    }
}

