#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <iostream>

#include <QString>
#include <QJsonObject>
#include <QtCore>
#include <QtGlobal>
#include <QJsonDocument>

#include "../core/command.h"
#include "../core/object.h"
#include "../core/attributes/resource.h"
#include "../core/attributes/moving.h"
#include "../core/gameworld.h"
#include "../core/attributes/damaging.h"
#include "../core/attributes/damageable.h"
#include "factory.h"
#include "../server/objectsignature.h"

namespace utils {

class Serializer {
  public:

    std::optional<QString> serializeGameWorld(const core::GameWorld& gameWorld);

    std::optional<QString> serializeObject(const core::Object& object);

    std::optional<QString> serializeObjectSignature(const server::ObjectSignature& signature);

    std::optional<QString> serializeCommand(const core::Command& command);

    std::optional<QString> serializeAttribute(const std::shared_ptr<core::Attribute>& attribute,
                                              std::function<std::optional<QJsonObject>(
                                                      const std::shared_ptr<core::Attribute>)> serializer);

    std::optional<core::GameWorld> deserializeGameWorld(const QString& serialized);

    std::optional<core::Object> deserializeObject(const QString& serialized);

    std::optional<server::ObjectSignature> deserializeObjectSignature(const QString& serialized);

    std::optional<core::Command> deserializeCommand(const QString& serialized);

    std::optional<std::shared_ptr<core::Attribute>> deserializeAttribute(const QString& serialized,
                                                                   std::function<std::optional<std::shared_ptr<core::Attribute>>(
                                                                           const QJsonObject&)> deserializer);

    void setPrettyPrinting(bool prettyPrinting);

    bool isPrettyPrinting();

    static std::optional<QJsonObject> gameWorldSerializer(const core::GameWorld& world);

    static std::optional<QJsonObject> commandSerializer(const core::Command& command);

    static std::optional<QJsonObject>
    objectSignatureSerializer(const server::ObjectSignature& signature);

    static std::optional<QJsonObject> objectSerializer(const core::Object& object);

    static std::optional<QJsonObject>
    resourceSerializer(const std::shared_ptr<core::Attribute>& attribute);

    static std::optional<QJsonObject>
    damagingSerializer(const std::shared_ptr<core::Attribute>& attribute);

    static std::optional<QJsonObject>
    damageableSerializer(const std::shared_ptr<core::Attribute>& attribute);

    static std::optional<QJsonObject>
    movingSerializer(const std::shared_ptr<core::Attribute>& moving);


    static std::optional<core::GameWorld> gameWorldDeserialize(const QJsonObject& serialized);

    static std::optional<core::Command> commandDeserializer(const QJsonObject& serialized);

    static std::optional<server::ObjectSignature>
    objectSignatureDeserializer(const QJsonObject& serialized);

    static std::optional<core::Object> objectDeserializer(const QJsonObject& serialized);

    static std::optional<std::shared_ptr<core::Attribute>>
    resourceDeserializer(const QJsonObject& serialized);

    static std::optional<std::shared_ptr<core::Attribute>>
    damagingDeserializer(const QJsonObject& serialized);

    static std::optional<std::shared_ptr<core::Attribute>>
    damageableDeserializer(const QJsonObject& serialized);

    static std::optional<std::shared_ptr<core::Attribute>>
    movingDeserializer(const QJsonObject& serialized);

    QString jsonObjectToString(const QJsonObject& jsonObject);

    std::optional<QJsonObject> stringToJsonObject(const QString& jsonString);

  private:

    bool prettyPrinting = true;
};

}  // namespace core

#endif // SERIALIZER_H
