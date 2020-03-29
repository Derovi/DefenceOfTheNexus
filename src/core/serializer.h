//
// Created by ok-PC on 24.03.2020.
//

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
    static void addJsonObject(const core::Object& object, QJsonObject& myJson);

    static void addJsonResource(const core::Resource& object, QJsonObject& myJson);

    static void addJsonDamaging(const core::Damaging& object, QJsonObject& myJson);

    static void addJsonDamageable(const core::Damageable& object, QJsonObject& myJson);

    static void addJsonMoving(const core::Moving& object, QJsonObject& myJson);

    static void finish(const QJsonObject& myObject, QString& serialized);

    static bool objectFromString(const QString& in, QJsonObject& myJson);

    static bool buildObject(core::Object& object,
                            const QJsonObject& myJson);

    static bool buildResourse(core::Resource& object, const QJsonObject& myJson);

    static bool buildDamaging(core::Damaging& object, const QJsonObject& myJson);

    static bool buildDamageable(core::Damageable& object, const QJsonObject& myJson);

    static bool buildMoving(core::Moving& object, const QJsonObject& myJson);
};

}  // namespace core

#endif //SERIALIZER_H
