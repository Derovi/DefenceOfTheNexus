#include "serializer.h"

std::optional<QString> core::Serializer::serializeGameWorld(const core::GameWorld& gameWorld) {
    return std::nullopt;
}

std::optional<QString> core::Serializer::serializeObject(const core::Object& object) {
    return std::nullopt;
}

std::optional<QString>
core::Serializer::serializeAttribute(const std::shared_ptr<core::Attribute> attribute,
                                     std::function<std::optional<QJsonObject>(
                                             const std::shared_ptr<core::Attribute>)> serializer) {
    return std::nullopt;
}

std::optional<core::GameWorld> core::Serializer::deserializeGameWorld(const QString& serialized) {
    return std::nullopt;
}

std::optional<core::Object> core::Serializer::deserializeObject(const QString& serialized) {
    return std::nullopt;
}

std::optional<std::shared_ptr<core::Attribute>>
core::Serializer::deserializeAttribute(const QString& serialized,
                                       std::function<std::optional<std::shared_ptr<Attribute>>(
                                               const QJsonObject&)> deserializer) {
    return std::nullopt;
}

void core::Serializer::setPrettyPrinting(bool prettyPrinting) {

}

bool core::Serializer::isPrettyPrinting() {
    return false;
}

std::optional<QJsonObject> core::Serializer::objectSerializer(const core::Object& object) {
    return std::nullopt;
}

std::optional<QJsonObject>
core::Serializer::resourceSerializer(const std::shared_ptr<core::Attribute> attribute) {
    return std::nullopt;
}

std::optional<QJsonObject>
core::Serializer::damagingSerializer(const std::shared_ptr<core::Attribute> attribute) {
    return std::nullopt;
}

std::optional<QJsonObject>
core::Serializer::damageableSerializer(const std::shared_ptr<core::Attribute> attribute) {
    return std::nullopt;
}

std::optional<QJsonObject>
core::Serializer::movingSerializer(const std::shared_ptr<core::Attribute> moving) {
    return std::nullopt;
}

std::optional<core::Object> core::Serializer::objectDeserializer(const QJsonObject& serialized) {
    return std::nullopt;
}

std::optional<std::shared_ptr<core::Attribute>>
core::Serializer::resourceDeserializer(const QJsonObject& serialized) {
    return nullptr;
}

std::optional<std::shared_ptr<core::Attribute>>
core::Serializer::damagingDeserializer(const QJsonObject& serialized) {
    return nullptr;
}

std::optional<std::shared_ptr<core::Attribute>>
core::Serializer::damageableDeserializer(const QJsonObject& serialized) {
    return nullptr;
}

std::optional<std::shared_ptr<core::Attribute>>
core::Serializer::movingDeserializer(const QJsonObject& serialized) {
    return nullptr;
}
