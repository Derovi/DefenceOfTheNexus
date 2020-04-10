#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QHash>

#include "../../core/gameworld.h"
#include "../../core/object.h"
#include "../strategies/strategy.h"

namespace server {

class Controller {
  public:
    Controller(core::Object* object);

    virtual void tick(core::GameWorld* world, double timeDelta);

    virtual core::Object* getObject();

    virtual ~Controller() = default;

    void addStrategy(const QString& strategyName);

    void removeStrategy(const QString& strategyName);

    void addStrategies(const QStringList& strategyNames);

    void removeStrategies(const QStringList& strategyNames);

    virtual DataBundle createDataBundle();

    const QHash<QString, Strategy*>& getStrategies() const;

    const QLinkedList<Strategy*>& getStrategiesByPriority() const;

  private:

    QHash<QString, Strategy*> strategies;
    QLinkedList<Strategy*> strategiesByPriority;
    core::Object* object;

    void prepare();

    void prepareStrategy(server::Strategy* strategy,
                    QHash<QString, int>& nameToVisitIteration,
                    int currentIteration);
};

}

#endif //CONTROLLER_H
