#ifndef FACTORY_H
#define FACTORY_H

#include <functional>

#include <QHash>
#include <QString>

#include "../core/object.h"
#include "../server/strategies/strategy.h"
#include "../server/controllers/unitcontroller.h"
#include "../server/controllers/gameworldcontroller.h"
#include "../server/controllers/controller.h"

namespace utils {

class Factory {
  public:
    static server::Controller* createController(core::Object* object);

    static void registerController(
            const QString& typeName,
            std::function<server::Controller*(core::Object*)> creator);

    static void registerStrategy(
            const QString& strategyName,
            std::function<server::Strategy*(server::Controller*)> creator);

  private:
    static QHash<QString, std::function<server::Controller*(core::Object*)>> controllerCreators;

    static QHash<QString, std::function<server::Strategy*(server::Controller*)>> strategyCreators;
};

}

#endif //FACTORY_H
