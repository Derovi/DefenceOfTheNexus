#ifndef FACTORY_H
#define FACTORY_H

#include <functional>
#include <optional>

#include <QJsonObject>
#include <QHash>
#include <QString>

#include "../client/objectgraphicsdescription.h"
#include "../core/object.h"
#include "../core/attribute.h"
#include "../server/strategies/strategy.h"
#include "../server/controllers/gameworldcontroller.h"
#include "../server/controllers/controller.h"

namespace utils {

class Factory {
  public:

    static std::shared_ptr<server::Strategy>
    createStrategy(const QString& strategyName, std::shared_ptr<core::Object> object);

    static std::function<std::optional<QJsonObject>(const std::shared_ptr<core::Attribute>)>
    getSerializer(const QString& attributeName);

    static std::function<std::optional<std::shared_ptr<core::Attribute>>(const QJsonObject&)>
    getDeserializer(const QString& attributeName);

    static std::optional<client::ObjectGraphicsDescription>
    getObjectGraphicsDescription(const QString& objectName);

    static void registerStrategy(
            const QString& strategyName,
            std::function<std::shared_ptr<server::Strategy>(
                    std::shared_ptr<core::Object>)> creator);

    static void registerObjectGraphicsDescription(const QString& objectName,
                                                  const client::ObjectGraphicsDescription& description);

    static void registerAttribute(
            const QString& attributeName,
            std::function<std::optional<QJsonObject>(
                    const std::shared_ptr<core::Attribute>)> serializer,
            std::function<std::optional<std::shared_ptr<core::Attribute>>(
                    const QJsonObject&)> deserializer);

  private:

    static QHash<QString, std::function<std::shared_ptr<server::Strategy>(
            std::shared_ptr<core::Object>)>> strategyCreators;

    static QHash<QString, std::function<std::optional<QJsonObject>(
            const std::shared_ptr<core::Attribute>)>> attributeSerializers;

    static QHash<QString, std::function<std::optional<std::shared_ptr<core::Attribute>>(
            const QJsonObject&)>> attributeDeserializers;

    static QHash<QString, client::ObjectGraphicsDescription> graphicsDescriptions;
};

}

#endif //FACTORY_H
