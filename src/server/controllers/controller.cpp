#include <memory>
#include <QDebug>
#include <QVector>

#include "../../utils/factory.h"
#include "controller.h"


server::Controller::Controller(std::shared_ptr<core::Object> object): object(object) {
    addStrategies(object->getStrategies());
}

const QHash<QString, std::shared_ptr<server::Strategy>>& server::Controller::getStrategies() const {
    return strategies;
}

void server::Controller::addStrategy(const QString& strategyName) {
    addStrategies(QStringList(strategyName));
}

void server::Controller::removeStrategy(const QString& strategyName) {
    removeStrategies(QStringList(strategyName));
}

void server::Controller::addStrategies(const QStringList& strategyNames) {
    for (const QString& strategyName : strategyNames) {
        if (strategies.contains(strategyName)) {
            continue;
        }
        std::shared_ptr<Strategy> strategy = utils::Factory::createStrategy(strategyName,
                                                                            getObject());
        if (strategy) {
            strategies.insert(strategyName, strategy);
        }
    }
    prepare();
    linkStrategies();
}

void server::Controller::removeStrategies(const QStringList& strategyNames) {
    for (const QString& strategyName : strategyNames) {
        if (!strategies.contains(strategyName)) {
            continue;
        }
        strategies.remove(strategyName);
    }
    prepare();
    linkStrategies();
}

std::shared_ptr<core::Object> server::Controller::getObject() {
    return object;
}

void server::Controller::tick(std::shared_ptr<core::GameWorld> world, double timeDelta) {
    for (std::shared_ptr<Strategy> strategy : strategiesByPriority) {
        strategy->tick(world, timeDelta);
    }
}

server::DataBundle server::Controller::createDataBundle(DataBundle baseBundle) {
    for (std::shared_ptr<core::Attribute> attribute : object->getAttributes()) {
        baseBundle.registerVariable(attribute->getAttributeName(), attribute);
    }
    return baseBundle;
}

const QLinkedList<std::shared_ptr<server::Strategy>>&
server::Controller::getStrategiesByPriority() const {
    return strategiesByPriority;
}

void server::Controller::prepare() {
    strategiesByPriority.clear();
    QHash<QString, int> nameToVisitIteration;
    int currentIteration = 1;
    for (std::shared_ptr<Strategy> strategy : strategies.values()) {
        if (nameToVisitIteration[strategy->getName()] == 0) {
            prepareStrategy(strategy, nameToVisitIteration, currentIteration++);
        }
    }
}

void server::Controller::prepareStrategy(std::shared_ptr<server::Strategy> strategy,
                                         QHash<QString, int>& nameToVisitIteration,
                                         int currentIteration) {
    bool isStrategyDependenciesCorrect = true;
    for (const QString& attribute : strategy->getRequiredAttributes()) {
        if (!object->hasAttribute(attribute)) {
            isStrategyDependenciesCorrect = false;
            break;
        }
    }
    if (isStrategyDependenciesCorrect) {
        for (QString& needed : strategy->getStartAfter()) {
            if (!nameToVisitIteration.contains(needed)) {
                isStrategyDependenciesCorrect = false;
                break;
            }
            if (nameToVisitIteration[needed] == 0) {
                prepareStrategy(strategies[needed], nameToVisitIteration, currentIteration);
            }
            if (nameToVisitIteration[needed] != currentIteration) {
                isStrategyDependenciesCorrect = false;
                break;
            }
        }
    }
    if (isStrategyDependenciesCorrect) {
        strategiesByPriority.push_back(strategy);
        nameToVisitIteration[strategy->getName()] = currentIteration;
    } else {
        nameToVisitIteration[strategy->getName()] = -1;
    }
}

void server::Controller::linkStrategies(const server::DataBundle& baseBundle) {
    DataBundle dataBundle = createDataBundle(baseBundle);
    //qDebug() << "link!" << object->getId() << strategiesByPriority.size();
    for (std::shared_ptr<Strategy> strategy : strategiesByPriority) {
        //qDebug() << "assign!";
        strategy->assign(dataBundle);
    }
}

void server::Controller::cancelTargets() {
    for (auto strategy : strategiesByPriority) {
        strategy->cancelTargets();
    }
}
