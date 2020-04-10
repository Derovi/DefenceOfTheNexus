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

    void resumeStrategy(const QString& strategyName);

    void pauseStrategy(const QString& strategyName);

    void addStrategies(const QStringList& strategyNames);

    void removeStrategies(const QStringList& strategyNames);

    void resumeStrategies(const QStringList& strategyNames);

    void pauseStrategies(const QStringList& strategyNames);

    virtual DataBundle createDataBundle();

    const QHash<QString, Strategy*>& getStrategies() const;

  private:

    QHash<QString, Strategy*> strategies;
    core::Object* object;
};

}

#endif //CONTROLLER_H
