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
    void serialize(const core::Object& object, QString& serialized);

    void serialize(const core::Resource& object, QString& serialized);

    void serialize(const core::ResourceBundle& object, QString& serialized);

    void serialize(const core::Moving& object, QString& serialized);

    void serialize(const core::GameWorld& object, QString& serialized);

    void serialize(const core::Damaging& object, QString& serialized);

    void serialize(const core::Building& object, QString& serialized);

    void serialize(const core::Damageable& object, QString& serialized);

    void serialize(const core::Unit& object, QString& serialized);

    bool deserialize(core::Object& object, const QString& serialized);

    bool deserialize(core::Resource& object, const QString& serialized);

    bool deserialize(core::ResourceBundle& object, const QString& serialized);

    bool deserialize(core::Moving& object, const QString& serialized);

    bool deserialize(core::GameWorld& object, const QString& serialized);

    bool deserialize(core::Damaging& object, const QString& serialized);

    bool deserialize(core::Building& object, const QString& serialized);

    bool deserialize(core::Damageable& object, const QString& serialized);

    bool deserialize(core::Unit& object, const QString& serialized);

  private:
    void addJsonObject(const core::Object& object, QJsonObject& json);

    void addJsonResource(const core::Resource& object, QJsonObject& json);

    void addJsonDamaging(const core::Damaging& object, QJsonObject& json);

    void addJsonDamageable(const core::Damageable& object, QJsonObject& json);

    void addJsonMoving(const core::Moving& object, QJsonObject& json);

    void convertJsonToString(const QJsonObject& Object, QString& serialized);

    bool objectFromString(const QString& in, QJsonObject& json);

    bool buildObject(core::Object& object, const QJsonObject& json);

    bool buildResourse(core::Resource& object, const QJsonObject& json);

    bool buildDamaging(core::Damaging& object, const QJsonObject& json);

    bool buildDamageable(core::Damageable& object, const QJsonObject& json);

    bool buildMoving(core::Moving& object, const QJsonObject& json);
};

}  // namespace core

#endif // SERIALIZER_H
