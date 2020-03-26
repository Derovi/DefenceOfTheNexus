//
// Created by ok-PC on 24.03.2020.
//

#include "serializer.h"

void core::Serializer::serialize(const core::Object& object, QString& serialized) {

}

void core::Serializer::serialize(const core::Resource& object, QString& serialized) {

}

void core::Serializer::serialize(const core::Moving& object, QString& serialized) {

}

void core::Serializer::serialize(const core::GameWorld& object, QString& serialized) {

}

void core::Serializer::serialize(const core::ResourceBundle& object, QString& serialized) {

}

void core::Serializer::serialize(const core::Damaging& object, QString& serialized) {

}

void core::Serializer::serialize(const core::Building& object, QString& serialized) {

}

void core::Serializer::serialize(const core::Damageable& object, QString& serialized) {

}

bool core::Serializer::deserialize(const core::Object& object, const QString& serialized) {
    return false;
}

bool core::Serializer::deserialize(const core::Resource& object, const QString& serialized) {
    return false;
}

bool core::Serializer::deserialize(const core::ResourceBundle& object, const QString& serialized) {
    return false;
}

bool core::Serializer::deserialize(const core::Moving& object, const QString& serialized) {
    return false;
}

bool core::Serializer::deserialize(const core::GameWorld& object, const QString& serialized) {
    return false;
}

bool core::Serializer::deserialize(const core::Damaging& object, const QString& serialized) {
    return false;
}

bool core::Serializer::deserialize(const core::Building& object, const QString& serialized) {
    return false;
}

bool core::Serializer::deserialize(const core::Damageable& object, const QString& serialized) {
    return false;
}
