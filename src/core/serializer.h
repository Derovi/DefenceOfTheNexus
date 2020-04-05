#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <iostream>

#include <QString>
#include <QJsonObject>
#include <QtCore>
#include <QtGlobal>

#include "object.h"
#include "resource.h"
#include "resourcebundle.h"
#include "moving.h"
#include "gameworld.h"
#include "damaging.h"
#include "damageable.h"
#include "building.h"
#include "unit.h"

namespace core {

class Serializer {
  public:
    static void serialize(const core::Object& object, QString& serialized);

    static void serialize(const core::Resource& object, QString& serialized);

    static void serialize(const core::ResourceBundle& object, QString& serialized);

    static void serialize(const core::Moving& object, QString& serialized);

    static void serialize(const core::GameWorld& object, QString& serialized);

    static void serialize(const core::Damaging& object, QString& serialized);

    static void serialize(const core::Building& object, QString& serialized);

    static void serialize(const core::Damageable& object, QString& serialized);

    static void serialize(const core::Unit& object, QString& serialized);

    static bool deserialize(core::Object& object, const QString& serialized);

    static bool deserialize(core::Resource& object, const QString& serialized);

    static bool deserialize(core::ResourceBundle& object, const QString& serialized);

    static bool deserialize(core::Moving& object, const QString& serialized);

    static bool deserialize(core::GameWorld& object, const QString& serialized);

    static bool deserialize(core::Damaging& object, const QString& serialized);

    static bool deserialize(core::Building& object, const QString& serialized);

    static bool deserialize(core::Damageable& object, const QString& serialized);

    static bool deserialize(core::Unit& object, const QString& serialized);

  private:
    static void addJsonObject(const core::Object& object, QJsonObject& json);

    static void addJsonResource(const core::Resource& object, QJsonObject& json);

    static void addJsonDamaging(const core::Damaging& object, QJsonObject& json);

    static void addJsonDamageable(const core::Damageable& object, QJsonObject& json);

    static void addJsonMoving(const core::Moving& object, QJsonObject& json);

    static void convertJsonToString(const QJsonObject& Object, QString& serialized);

    static bool objectFromString(const QString& in, QJsonObject& json);

    static bool buildObject(core::Object& object, const QJsonObject& json);

    static bool buildResourse(core::Resource& object, const QJsonObject& json);

    static bool buildDamaging(core::Damaging& object, const QJsonObject& json);

    static bool buildDamageable(core::Damageable& object, const QJsonObject& json);

    static bool buildMoving(core::Moving& object, const QJsonObject& json);
};

}  // namespace core

#endif // SERIALIZER_H
