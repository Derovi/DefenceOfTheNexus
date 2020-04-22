#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QHash>

#include "../../core/gameworld.h"
#include "../../core/object.h"
#include "../strategies/strategy.h"

namespace server {

class Controller {
  public:
    Controller(std::shared_ptr<core::Object> object);

    void tick(std::shared_ptr<core::GameWorld> world, double timeDelta);

    std::shared_ptr<core::Object> getObject();

    ~Controller() = default;

    void linkStrategies(const DataBundle& baseBundle = DataBundle());

    void addStrategy(const QString& strategyName);

    void removeStrategy(const QString& strategyName);

    void addStrategies(const QStringList& strategyNames);

    void removeStrategies(const QStringList& strategyNames);

    void cancelTargets();

    const QHash<QString, std::shared_ptr<Strategy>>& getStrategies() const;

    const QLinkedList<std::shared_ptr<Strategy>>& getStrategiesByPriority() const;

  private:

    //TODO optimize
    QHash<QString, std::shared_ptr<Strategy>> strategies;
    QLinkedList<std::shared_ptr<Strategy>> strategiesByPriority;
    std::shared_ptr<core::Object> object;

    DataBundle createDataBundle(DataBundle baseBundle = DataBundle());

    void prepare();

    void prepareStrategy(std::shared_ptr<server::Strategy> strategy,
                    QHash<QString, int>& nameToVisitIteration,
                    int currentIteration);
};

}

#endif //CONTROLLER_H
