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

    static server::Strategy* createStrategy(const QString& strategyName, core::Object* object,
                                            server::DataBundle& dataBundle);

    static void registerController(
            const QString& typeName,
            std::function<server::Controller*(core::Object*)> creator);

    static void registerStrategy(
            const QString& strategyName,
            std::function<server::Strategy*(core::Object*, server::DataBundle&)> creator);

  private:
    static QHash<QString, std::function<server::Controller*(core::Object*)>> controllerCreators;

    static QHash<QString, std::function<server::Strategy*(core::Object*,
                                                          server::DataBundle&)>> strategyCreators;
};

}

#endif //FACTORY_H
