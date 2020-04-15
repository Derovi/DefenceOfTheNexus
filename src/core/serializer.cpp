#include "serializer.h"

std::optional<QString> core::Serializer::serializeGameWorld(const core::GameWorld& gameWorld) {
    auto result = gameWorldSerializer(gameWorld);
    if(result==std::nullopt){
        return std::nullopt;
    }
    QJsonDocument doc(result.value());
    QString strJson(doc.toJson(QJsonDocument::Compact));
    return strJson;
}

std::optional<QString> core::Serializer::serializeObject(const core::Object& object) {
    auto result = objectSerializer(object);
    if(result==std::nullopt){
        return std::nullopt;
    }
    QJsonDocument doc(result.value());
    QString strJson(doc.toJson(QJsonDocument::Compact));
    return strJson;
}

std::optional<QString>
core::Serializer::serializeAttribute(const std::shared_ptr<core::Attribute> attribute,
                                     std::function<std::optional<QJsonObject>(
                                             const std::shared_ptr<core::Attribute>)> serializer) {
    auto result = serializer(attribute);
    if(result==std::nullopt){
        return std::nullopt;
    }
    QJsonDocument doc(result.value());
    QString strJson(doc.toJson(QJsonDocument::Compact));
    return strJson;
}

std::optional<core::GameWorld> core::Serializer::deserializeGameWorld(const QString& serialized) {
    QJsonObject json;
    QJsonDocument doc = QJsonDocument::fromJson(serialized.toUtf8());
    if (doc.isNull() || !doc.isObject()) {
        return std::nullopt;
    }
    json = doc.object();
    return gameWorldDeserialize(json);
}

std::optional<core::Object> core::Serializer::deserializeObject(const QString& serialized) {
    QJsonObject json;
    QJsonDocument doc = QJsonDocument::fromJson(serialized.toUtf8());
    if (doc.isNull() || !doc.isObject()) {
        return std::nullopt;
    }
    json = doc.object();
    return objectDeserializer(json);
}

std::optional<std::shared_ptr<core::Attribute>>
core::Serializer::deserializeAttribute(const QString& serialized,
                                       std::function<std::optional<std::shared_ptr<Attribute>>(
                                               const QJsonObject&)> deserializer) {
    QJsonObject json;
    QJsonDocument doc = QJsonDocument::fromJson(serialized.toUtf8());
    if (doc.isNull() || !doc.isObject()) {
        return std::nullopt;
    }
    json = doc.object();
    return deserializer(json);
}

void core::Serializer::setPrettyPrinting(bool prettyPrinting) {

}

bool core::Serializer::isPrettyPrinting() {
    return false;
}

std::optional<QJsonObject> core::Serializer::objectSerializer(const core::Object& object) {
    QJsonObject json;
    QJsonObject polygon;
    QJsonObject position;
    json.insert("id", QString::number(object.getId()));
    position.insert("x", object.getPosition().x());
    position.insert("y", object.getPosition().y());
    json.insert("position", position);
    json.insert("rotationAngle", object.getRotationAngle());
    QPolygonF hitbox = object.getHitbox();
    int iter = 0;
    QJsonArray xArray, yArray;
    for (const auto& i : hitbox) {
        xArray.push_back(i.x());
        yArray.push_back(i.y());
        iter++;
    }
    position.remove("x");
    position.remove("y");
    position.insert("x", xArray);
    position.insert("y", yArray);
    json.insert("hitbox", position);
    json.insert("typeName", object.getTypeName());
    QJsonObject attributes;
    for (const auto& attribute : object.getAttributes()) {
        std::optional<QJsonObject> result = utils::Factory::getSerializer(
                attribute->getAttributeName())(attribute);
        if (result == std::nullopt) {
            return std::nullopt;
        }
        attributes.insert(attribute->getAttributeName(), result.value());
    }
    json.insert("attributes", attributes);
    return json;
}

std::optional<QJsonObject>
core::Serializer::resourceSerializer(const std::shared_ptr<core::Attribute> attribute) {
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
core::Serializer::damagingSerializer(const std::shared_ptr<core::Attribute> attribute) {
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
core::Serializer::damageableSerializer(const std::shared_ptr<core::Attribute> attribute) {
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
core::Serializer::movingSerializer(const std::shared_ptr<core::Attribute> attribute) {
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

std::optional<core::Object> core::Serializer::objectDeserializer(const QJsonObject& json) {

    if (!json["id"].isString()) {
        return std::nullopt;
    }
    QString idStr = json["id"].toString();
    bool ok = false;
    uint64_t id = idStr.toULongLong(&ok);
    if (!ok) {
        return std::nullopt;
    }
    QJsonObject pos;
    if (!json["position"].isObject()) {
        return std::nullopt;
    }
    pos = (json["position"]).toObject();
    auto iterPos = pos.begin();
    if (!(*iterPos).isDouble()) {
        return std::nullopt;
    }
    double x = (*iterPos).toDouble();
    iterPos++;
    if (!(*iterPos).isDouble()) {
        return std::nullopt;
    }
    double y = (*iterPos).toDouble();
    iterPos++;
    QPointF point(x, y);
    if (!json["rotationAngle"].isDouble()) {
        return std::nullopt;
    }
    QVector<QPointF> vec;
    if (!json["hitbox"].isObject()) {
        return std::nullopt;
    }
    pos = json["hitbox"].toObject();
    iterPos = pos.begin();
    if (!(*iterPos).isArray()) {
        return std::nullopt;
    }
    QJsonArray xArray = (*iterPos).toArray();
    iterPos++;
    if (!(*iterPos).isArray()) {
        return std::nullopt;
    }
    QJsonArray yArray = (*iterPos).toArray();
    if (xArray.size() != yArray.size()) {
        return std::nullopt;
    }
    for (const auto& i : xArray) {
        if (!i.isDouble()) {
            return std::nullopt;
        }
        vec.push_back(QPointF(i.toDouble(), 0));
    }
    int it = 0;
    for (const auto& i : yArray) {
        if (!i.isDouble()) {
            return std::nullopt;
        }
        vec[it].setY(qreal(i.toDouble()));
    }
    if (!json["typeName"].isString()) {
        return std::nullopt;
    }
    core::Object ans = core::Object(id, json["typeName"].toString(), point, QPolygonF(vec),
                                    json["rotationAngle"].toDouble());
    QJsonObject attributes;
    if (!json["attributes"].isObject()) {
        return std::nullopt;
    }
    attributes = json["attributes"].toObject();
    QLinkedList<std::shared_ptr<Attribute> > objectAttributes;
    auto iter = attributes.begin();
    while (iter != attributes.end()) {
        if (!iter.value().isObject()) {
            return std::nullopt;
        }
        QJsonObject attribute = iter.value().toObject();
        std::optional<std::shared_ptr<Attribute>> result = utils::Factory::getDeserializer(
                iter.key())(attribute);
        if (result == std::nullopt) {
            return std::nullopt;
        }
        objectAttributes.push_back(result.value());
        iter++;
    }
    ans.setAttributes(objectAttributes);
    return ans;
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

std::optional<QJsonObject> core::Serializer::gameWorldSerializer(const core::GameWorld& world) {
    QJsonObject json;
    json.insert("width", world.getWidth());
    json.insert("height", world.getHeight());
    QJsonArray resources;
    QJsonObject object;
    QVector<core::Resource> resVector = world.getResources();
    for (auto res : resVector) {
        std::optional<QJsonObject> result = resourceSerializer(
                std::make_shared<core::Resource>(res));
        if (result == std::nullopt) {
            return std::nullopt;
        }
        resources.insert(resources.size(), result.value());
    }
    auto iter = world.getObjects().begin();
    while (iter != world.getObjects().end()) {
        std::optional<QJsonObject> result = objectSerializer(*iter.value());
        if (result == std::nullopt) {
            return result;
        }
        object.insert(QString::number(iter.key()), result.value());
    }
    json.insert("resources", resources);
    json.insert("objects", object);
    return json;
}

std::optional<core::GameWorld>
core::Serializer::gameWorldDeserialize(const QJsonObject& serialized) {
    core::GameWorld ans;
    if (!serialized["width"].isDouble()) {
        return std::nullopt;
    }
    ans.setWidth(serialized["width"].toDouble());
    if (!serialized["height"].isDouble()) {
        return std::nullopt;
    }
    ans.setHeight(serialized["height"].toDouble());
    QJsonArray resources;
    if (!serialized["resources"].isArray()) {
        return std::nullopt;
    }
    resources = serialized["resources"].toArray();
    QVector<core::Resource> resVector;
    for (const auto& res : resources) {
        if (!res.isObject()) {
            return std::nullopt;
        }
        auto resource = resourceDeserializer(res.toObject());
        if (resource == std::nullopt) {
            return std::nullopt;
        }
        resVector.push_back(*dynamic_cast<core::Resource*>(resource.value().get()));
    }
    ans.setResources(resVector);
    if (serialized["objects"].isObject()) {
        return std::nullopt;
    }
    QJsonObject objects = serialized["objects"].toObject();
    QHash<int64_t, std::shared_ptr<core::Object>> hashObjects;
    auto iter = objects.begin();
    while (iter != objects.end()) {
        if (!iter.value().isObject()) {
            return std::nullopt;
        }
        auto result = objectDeserializer(iter.value().toObject());
        if (result == std::nullopt) {
            return std::nullopt;
        }
        hashObjects[iter.key().toLongLong()] = std::make_shared<core::Object>(result.value());
    }
    ans.setObjects(hashObjects);
    return ans;
}
