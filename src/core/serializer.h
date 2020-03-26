//
// Created by ok-PC on 24.03.2020.
//

#ifndef SERIALIZER_H
#define SERIALIZER_H

#include<QString>
#include "object.h"
#include "resource.h"
#include "resourcebundle.h"
#include "moving.h"
#include "gameworld.h"
#include "damaging.h"
#include "damageable.h"
#include "building.h"

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

    static bool deserialize(const core::Object& object, const QString& serialized);

    static bool deserialize(const core::Resource& object, const QString& serialized);

    static bool deserialize(const core::ResourceBundle& object, const QString& serialized);

    static bool deserialize(const core::Moving& object, const QString& serialized);

    static bool deserialize(const core::GameWorld& object, const QString& serialized);

    static bool deserialize(const core::Damaging& object, const QString& serialized);

    static bool deserialize(const core::Building& object, const QString& serialized);

    static bool deserialize(const core::Damageable& object, const QString& serialized);


};
}

#endif //SERIALIZER_H
