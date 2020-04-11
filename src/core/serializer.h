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

    std::optional<QString> serializeAttribute(const core::Attribute* attribute,
                                     std::function<std::optional<QJsonObject>(
                                             const core::Attribute*)> serializer);

    std::optional<GameWorld> deserializeGameWorld(const QString& serialized);

    std::optional<Object> deserializeObject(const QString& serialized);

    std::optional<Attribute*> deserializeAttribute(const QString& serialized,
                                          std::function<std::optional<Attribute*>(
                                                  const QJsonObject&)> deserializer);

    void setPrettyPrinting(bool prettyPrinting);

    bool isPrettyPrinting();

    static std::optional<QJsonObject> objectSerializer(const core::Object& object);

    static std::optional<QJsonObject> resourceSerializer(const core::Attribute* attribute);

    static std::optional<QJsonObject> damagingSerializer(const core::Attribute* attribute);

    static std::optional<QJsonObject> damageableSerializer(const core::Attribute* attribute);

    static std::optional<QJsonObject> movingSerializer(const core::Attribute* moving);


    static std::optional<core::Object> objectDeserializer(const QJsonObject& serialized);

    static std::optional<core::Attribute*> resourceDeserializer(const QJsonObject& serialized);

    static std::optional<core::Attribute*> damagingDeserializer(const QJsonObject& serialized);

    static std::optional<core::Attribute*> damageableDeserializer(const QJsonObject& serialized);

    static std::optional<core::Attribute*> movingDeserializer(const QJsonObject& serialized);

  private:

    bool prettyPrinting = true;
};

}  // namespace core

#endif // SERIALIZER_H
