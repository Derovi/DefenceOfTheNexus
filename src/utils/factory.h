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
#include "../server/objectsignature.h"
#include "keymanager.h"

namespace utils {

class Factory {
  public:
    static std::shared_ptr<server::Strategy>
    createStrategy(const QString& strategyName, const std::shared_ptr<core::Object>& object);

    static std::shared_ptr<client::SpriteController>
    createSpriteController(const QString& spriteControllerName,
                           const std::shared_ptr<core::Object>& object);

    static std::function<std::optional<QJsonObject>(const std::shared_ptr<core::Attribute>)>
    getSerializer(const QString& attributeName);

    static std::function<QJsonObject(
            const std::shared_ptr<core::Attribute>& beforeChanges,
            const std::shared_ptr<core::Attribute>& afterChanges,
            const utils::KeyManager& keyManager)> getPartSerializer(const QString& attributeName);

    static std::function<std::optional<std::shared_ptr<core::Attribute>>(const QJsonObject&)>
    getDeserializer(const QString& attributeName);

    static std::function<void(
            const std::shared_ptr<core::Attribute>& resource,
            const QJsonObject& changes,
            const utils::KeyManager& keyManager)>
    getPartDeserializer(const QString& attributeName);

    static std::optional<client::ObjectGraphicsDescription>
    getObjectGraphicsDescription(const QString& objectName);

    static std::optional<server::ObjectSignature>
    getObjectSignature(const QString& objectName);

    static void registerStrategy(
            const QString& strategyName,
            std::function<std::shared_ptr<server::Strategy>(
                    std::shared_ptr<core::Object>)> creator);

    static void registerSpriteController(
            const QString& spriteControllerName,
            std::function<std::shared_ptr<client::SpriteController>(
                    std::shared_ptr<core::Object>)> creator);

    static void registerObjectGraphicsDescription(const QString& objectName,
                                                  const client::ObjectGraphicsDescription& description);

    static void registerObjectSignature(const QString& objectName,
                                        const server::ObjectSignature& signature);

    static void registerAttribute(
            const QString& attributeName,
            std::function<std::optional<QJsonObject>(
                    const std::shared_ptr<core::Attribute>)> serializer,
            std::function<std::optional<std::shared_ptr<core::Attribute>>(
                    const QJsonObject&)> deserializer,
            std::function<QJsonObject(
                    const std::shared_ptr<core::Attribute>& beforeChanges,
                    const std::shared_ptr<core::Attribute>& afterChanges,
                    const utils::KeyManager& partSerializer)>,
            std::function<void(
                    const std::shared_ptr<core::Attribute>& resource,
                    const QJsonObject& changes,
                    const utils::KeyManager& keyManager)> partDeserializer);

  private:
    static QHash<QString, std::function<std::shared_ptr<server::Strategy>(
            std::shared_ptr<core::Object>)>> strategyCreators;

    static QHash<QString, std::function<std::shared_ptr<client::SpriteController>(
            std::shared_ptr<core::Object>)>> spriteControllerCreators;

    static QHash<QString, std::function<std::optional<QJsonObject>(
            const std::shared_ptr<core::Attribute>)>> attributeSerializers;

    static QHash<QString, std::function<QJsonObject(
            const std::shared_ptr<core::Attribute>& beforeChanges,
            const std::shared_ptr<core::Attribute>& afterChanges,
            const utils::KeyManager& keyManager)>> attributePartSerializers;

    static QHash<QString, std::function<std::optional<std::shared_ptr<core::Attribute>>(
            const QJsonObject&)>> attributeDeserializers;

    static QHash<QString, std::function<void(
            const std::shared_ptr<core::Attribute>& resource,
            const QJsonObject& changes,
            const utils::KeyManager& keyManager)>> attributePartDeserializers;

    static QHash<QString, client::ObjectGraphicsDescription> graphicsDescriptions;

    static QHash<QString, server::ObjectSignature> objectSignatures;
};

}

#endif //FACTORY_H
