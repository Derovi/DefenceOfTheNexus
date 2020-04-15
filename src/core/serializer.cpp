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
core::Serializer::resourceSerializer(const std::shared_ptr<core::Attribute>& attribute) {
    auto object = dynamic_cast<core::Resource*>(attribute.get());
    QJsonObject json;
    if (object == nullptr) {
        return std::nullopt;
    }
    if (object->getType() == ResourceType::kWood) {
        json.insert("resourceType", 1);
    }
    if (object->getType() == ResourceType::kIron) {
        json.insert("resourceType", 2);
    }
    if (object->getType() == ResourceType::kStone) {
        json.insert("resourceType", 3);
    }
    json.insert("amount", object->getAmount());
    return json;
}

std::optional<QJsonObject>
core::Serializer::damagingSerializer(const std::shared_ptr<core::Attribute>& attribute) {
    auto object = dynamic_cast<core::Damaging*>(attribute.get());
    QJsonObject json;
    if (object == nullptr) {
        return std::nullopt;
    }
    json.insert("damage", object->getDamage());
    json.insert("radius", object->getAttackRadius());
    json.insert("delay", object->getAttackDelay());
    json.insert("bulletType", object->getBulletType());
    return json;
}

std::optional<QJsonObject>
core::Serializer::damageableSerializer(const std::shared_ptr<core::Attribute>& attribute) {
    auto object = dynamic_cast<core::Damageable*>(attribute.get());
    QJsonObject json;
    if (object == nullptr) {
        return std::nullopt;
    }
    json.insert("health", object->getHealth());
    json.insert("maxHealth", object->getMaxHealth());
    return json;
}

std::optional<QJsonObject>
core::Serializer::movingSerializer(const std::shared_ptr<core::Attribute>& attribute) {
    auto object = dynamic_cast<core::Moving*>(attribute.get());
    QJsonObject json;
    if (object == nullptr) {
        return std::nullopt;
    }
    QJsonObject direction;
    direction.insert("x", object->getDirection().x());
    direction.insert("y", object->getDirection().y());
    json.insert("direction", direction);
    json.insert("maxSpeed", object->getMaxSpeed());
    json.insert("speed", object->getSpeed());
    return json;
}

std::optional<core::Object> core::Serializer::objectDeserializer(const QJsonObject& serialized) {
    return std::nullopt;
}

std::optional<std::shared_ptr<core::Attribute>>
core::Serializer::resourceDeserializer(const QJsonObject& serialized) {
    if (!serialized["amount"].isDouble()) {
        return std::nullopt;
    }
    int amount = serialized["amount"].toDouble();

    if (!serialized["resourceType"].isDouble()) {
        return std::nullopt;
    }
    int type = serialized["resourceType"].toDouble();
    ResourceType resType;
    if (type == 1) {
        resType = ResourceType::kWood;
    }
    if (type == 2) {
        resType = ResourceType::kIron;
    }
    if (type == 3) {
        resType = ResourceType::kStone;
    }
    auto object = new core::Resource(resType, amount);
    return std::make_shared<core::Resource>(*object);
}

std::optional<std::shared_ptr<core::Attribute>>
core::Serializer::damagingDeserializer(const QJsonObject& serialized) {
    auto object = new core::Damaging;
    if (!serialized["bulletType"].isString()) {
        delete object;
        return std::nullopt;
    }
    object->setBulletType((serialized["bulletType"]).toString());
    if (!serialized["damage"].isDouble()) {
        delete object;
        return std::nullopt;
    }
    object->setDamage((serialized["damage"]).toDouble());
    if (!serialized["delay"].isDouble()) {
        delete object;
        return std::nullopt;
    }
    object->setAttackDelay((serialized["delay"]).toDouble());
    if (!serialized["radius"].isDouble()) {
        delete object;
        return std::nullopt;
    }
    object->setAttackRadius((serialized["radius"]).toDouble());
    return std::make_shared<core::Damaging>(*object);
}

std::optional<std::shared_ptr<core::Attribute>>
core::Serializer::damageableDeserializer(const QJsonObject& serialized) {
    auto object = new core::Damageable;
    if (!serialized["health"].isDouble()) {
        delete object;
        return std::nullopt;
    }
    object->setHealth(serialized["health"].toDouble());
    if (!serialized["maxHealth"].isDouble()) {
        delete object;
        return std::nullopt;
    }
    object->setMaxHealth(serialized["maxHealth"].toDouble());
    return std::make_shared<core::Damageable>(*object);
}

std::optional<std::shared_ptr<core::Attribute>>
core::Serializer::movingDeserializer(const QJsonObject& serialized) {
    auto object = new core::Moving;
    QJsonObject direction;
    if (!serialized["direction"].isObject()) {
        delete object;
        return std::nullopt;
    }
    direction = serialized["direction"].toObject();
    QJsonObject::Iterator dirIter = direction.begin();
    double x, y;
    if (!(dirIter)->isDouble()) {
        delete object;
        return std::nullopt;
    }
    x = (dirIter)->toDouble();
    dirIter++;
    if (!dirIter->isDouble()) {
        delete object;
        return std::nullopt;
    }
    y = (dirIter)->toDouble();
    object->setDirection(QVector2D(x, y));
    if (!serialized["maxSpeed"].isDouble()) {
        delete object;
        return std::nullopt;
    }
    object->setMaxSpeed(serialized["maxSpeed"].toDouble());
    if (!serialized["speed"].isDouble()) {
        delete object;
        return std::nullopt;
    }
    object->setSpeed(serialized["speed"].toDouble());
    return std::make_shared<core::Moving>(*object);
}
