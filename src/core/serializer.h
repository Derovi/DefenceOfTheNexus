//
// Created by ok-PC on 24.03.2020.
//

#ifndef SERIALIZER_H
#define SERIALIZER_H

#include<QString>
#include <QJsonObject>
#include <QtCore>
#include "object.h"
#include "resource.h"
#include "resourcebundle.h"
#include "moving.h"
#include "gameworld.h"
#include "damaging.h"
#include "damageable.h"
#include "building.h"
#include "unit.h"
#include <QtGlobal>

namespace core {
class Serializer {
    static void serialize(const core::Object& object, QString& serialized);

    static void serialize(const core::Resource& object, QString& serialized);

    static void serialize(const core::ResourceBundle& object, QString& serialized);

    static void serialize(const core::Moving& object, QString& serialized);

    static void serialize(const core::GameWorld& object, QString& serialized);

    static void serialize(const core::Damaging& object, QString& serialized);

    static void serialize(const core::Building& object, QString& serialized);

    static void serialize(const core::Damageable& object, QString& serialized);

    static void serialize(const core::Unit& object, QString& serialized);

    static bool deserialize(const core::Object& object, const QString& serialized);

    static bool deserialize(const core::Resource& object, const QString& serialized);

    static bool deserialize(const core::ResourceBundle& object, const QString& serialized);

    static bool deserialize(const core::Moving& object, const QString& serialized);

    static bool deserialize(const core::GameWorld& object, const QString& serialized);

    static bool deserialize(const core::Damaging& object, const QString& serialized);

    static bool deserialize(const core::Building& object, const QString& serialized);

    static bool deserialize(const core::Damageable& object, const QString& serialized);

    static bool deserialize(const core::Unit& object, const QString& serialized);

  private:
    static void addJsonObject(const core::Object& object, QJsonObject& my_json);

    static void addJsonResource(const core::Resource& object, QJsonObject& my_json);

    static void addJsonDamaging(const core::Damaging& object, QJsonObject& my_json);

    static void addJsonDamageable(const core::Damageable& object, QJsonObject& my_json);

    static void addJsonMoving(const core::Moving& object, QJsonObject& my_json);

    static void finish(const QJsonObject& my_object, QString& serialized);

    static bool objectFromString(const QString& in, QJsonObject& my_json);

    static bool buildObject(core::Object& object,
                            QJsonObject::iterator& iter);
};
}

#endif //SERIALIZER_H
