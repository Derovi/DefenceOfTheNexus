#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <iostream>

#include <QString>
#include <QJsonObject>
#include <QtCore>
#include <QtGlobal>

#include "object.h"
#include "resource.h"
#include "moving.h"
#include "gameworld.h"
#include "damaging.h"
#include "damageable.h"

namespace core {

class Serializer {
  public:

    std::optional<QString> serializeGameWorld(const core::GameWorld& gameWorld);

    std::optional<QString> serializeObject(const core::Object& object);

    std::optional<QString> serializeAttribute(const std::shared_ptr<core::Attribute> attribute,
                                              std::function<std::optional<QJsonObject>(
                                                      const std::shared_ptr<core::Attribute>)> serializer);

    std::optional<GameWorld> deserializeGameWorld(const QString& serialized);

    std::optional<Object> deserializeObject(const QString& serialized);

    std::optional<std::shared_ptr<Attribute>> deserializeAttribute(const QString& serialized,
                                                                   std::function<std::optional<std::shared_ptr<Attribute>>(
                                                                           const QJsonObject&)> deserializer);

    void setPrettyPrinting(bool prettyPrinting);

    bool isPrettyPrinting();

    static std::optional<QJsonObject> objectSerializer(const core::Object& object);

    static std::optional<QJsonObject>
    resourceSerializer(const std::shared_ptr<core::Attribute>& attribute);

    static std::optional<QJsonObject>
    damagingSerializer(const std::shared_ptr<core::Attribute>& attribute);

    static std::optional<QJsonObject>
    damageableSerializer(const std::shared_ptr<core::Attribute>& attribute);

    static std::optional<QJsonObject>
    movingSerializer(const std::shared_ptr<core::Attribute>& moving);


    static std::optional<core::Object> objectDeserializer(const QJsonObject& serialized);

    static std::optional<std::shared_ptr<core::Attribute>>
    resourceDeserializer(const QJsonObject& serialized);

    static std::optional<std::shared_ptr<core::Attribute>>
    damagingDeserializer(const QJsonObject& serialized);

    static std::optional<std::shared_ptr<core::Attribute>>
    damageableDeserializer(const QJsonObject& serialized);

    static std::optional<std::shared_ptr<core::Attribute>>
    movingDeserializer(const QJsonObject& serialized);

  private:

    bool prettyPrinting = true;

    QString jsonObjectToString(const QJsonObject& jsonObject);

    std::optional<QJsonObject> stringToJsonObject(const QString& jsonString);
};

}  // namespace core

#endif // SERIALIZER_H
