#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QHash>

#include "../../core/gameworld.h"
#include "../../core/object.h"
#include "../strategies/strategy.h"

namespace server {

class Controller {
  public:
    virtual void tick(core::GameWorld* world, double timeDelta) = 0;

    virtual core::Object* getObject() = 0;

    static Controller* createController(core::Object* object);

    virtual ~Controller() = default;

    void addStrategy(const QString& strategyName);

    void removeStrategy(const QString& strategyName);

    void resumeStrategy(const QString& strategyName);

    void pauseStrategy(const QString& strategyName);

    void addStrategies(const QStringList& strategyNames);

    void removeStrategies(const QStringList& strategyNames);

    void resumeStrategies(const QStringList& strategyNames);

    void pauseStrategies(const QStringList& strategyNames);

    const QHash<QString, Strategy>& getStrategies() const;

  private:
    QHash<QString, Strategy*> strategies;
};

}

#endif //CONTROLLER_H
