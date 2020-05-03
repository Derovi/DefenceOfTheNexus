#include "serializer.h"

utils::Serializer::Serializer(bool prettyPrinting) : prettyPrinting(prettyPrinting) {}

std::optional<QString> utils::Serializer::serializeGameWorld(const core::GameWorld& gameWorld) {
    auto result = gameWorldSerializer(gameWorld);
    if (result == std::nullopt) {
        return std::nullopt;
    }
    return jsonObjectToString(result.value());
}

std::optional<QString> utils::Serializer::serializeObject(const core::Object& object) {
    auto result = objectSerializer(object);
    if (result == std::nullopt) {
        return std::nullopt;
    }
    return jsonObjectToString(result.value());
}

std::optional<QString>
utils::Serializer::serializeAttribute(const std::shared_ptr<core::Attribute>& attribute,
                                      std::function<std::optional<QJsonObject>(
                                              const std::shared_ptr<core::Attribute>)> serializer) {
    auto result = serializer(attribute);
    if (result == std::nullopt) {
        return std::nullopt;
    }
    return jsonObjectToString(result.value());
}

std::optional<core::GameWorld> utils::Serializer::deserializeGameWorld(const QString& serialized) {
    std::optional<QJsonObject> json = stringToJsonObject(serialized);
    if (json == std::nullopt) {
        return std::nullopt;
    }
    return gameWorldDeserialize(json.value());
}

std::optional<core::Object> utils::Serializer::deserializeObject(const QString& serialized) {
    std::optional<QJsonObject> json = stringToJsonObject(serialized);
    if (json == std::nullopt) {
        return std::nullopt;
    }
    return objectDeserializer(json.value());
}

std::optional<std::shared_ptr<core::Attribute>>
utils::Serializer::deserializeAttribute(const QString& serialized,
                                        std::function<std::optional<std::shared_ptr<core::Attribute>>(
                                                const QJsonObject&)> deserializer) {
    std::optional<QJsonObject> json = stringToJsonObject(serialized);
    if (json == std::nullopt) {
        return std::nullopt;
    }
    return deserializer(json.value());
}

void utils::Serializer::setPrettyPrinting(bool prettyPrinting) {
    this->prettyPrinting = prettyPrinting;
}

bool utils::Serializer::isPrettyPrinting() {
    return prettyPrinting;
}

std::optional<QJsonObject> utils::Serializer::objectSerializer(const core::Object& object) {
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
        ++iter;
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
utils::Serializer::resourceSerializer(const std::shared_ptr<core::Attribute>& attribute) {
    auto object = dynamic_cast<core::Resource*>(attribute.get());
    QJsonObject json;
    if (object == nullptr) {
        return std::nullopt;
    }
    json.insert("resourceType", static_cast<int>(object->getType()));
    json.insert("amount", object->getAmount());
    json.insert("miningSpeedModifier", object->getMiningSpeedModifier());
    return json;
}

std::optional<QJsonObject>
utils::Serializer::damagingSerializer(const std::shared_ptr<core::Attribute>& attribute) {
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
utils::Serializer::damageableSerializer(const std::shared_ptr<core::Attribute>& attribute) {
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
utils::Serializer::movingSerializer(const std::shared_ptr<core::Attribute>& attribute) {
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

std::optional<QJsonObject>
utils::Serializer::miningSerializer(const std::shared_ptr<core::Attribute>& attribute) {
    auto object = dynamic_cast<core::Mining*>(attribute.get());
    QJsonObject json;
    if (object == nullptr) {
        return std::nullopt;
    }
    json.insert("miningSpeed", object->getMiningSpeed());
    json.insert("miningDelay", object->getMiningDelay());
    json.insert("miningRadius", object->getMiningRadius());
    json.insert("mining", object->isMining());
    return json;
}

std::optional<core::Object> utils::Serializer::objectDeserializer(const QJsonObject& json) {
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
    ++iterPos;
    if (!(*iterPos).isDouble()) {
        return std::nullopt;
    }
    double y = (*iterPos).toDouble();
    ++iterPos;
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
    ++iterPos;
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
        vec[it++].setY(qreal(i.toDouble()));
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
    QLinkedList<std::shared_ptr<core::Attribute> > objectAttributes;
    auto iter = attributes.begin();
    while (iter != attributes.end()) {
        if (!iter.value().isObject()) {
            return std::nullopt;
        }
        QJsonObject attribute = iter.value().toObject();
        std::optional<std::shared_ptr<core::Attribute>> result = utils::Factory::getDeserializer(
                iter.key())(attribute);
        if (result == std::nullopt) {
            return std::nullopt;
        }
        objectAttributes.push_back(result.value());
        ++iter;
    }
    ans.setAttributes(objectAttributes);
    return ans;
}

std::optional<std::shared_ptr<core::Attribute>>
utils::Serializer::resourceDeserializer(const QJsonObject& serialized) {
    if (!serialized["amount"].isDouble() || !serialized["resourceType"].isDouble()
        || !serialized["miningSpeedModifier"].isDouble()) {
        return std::nullopt;
    }
    int amount = serialized["amount"].toDouble();
    int type = serialized["resourceType"].toDouble();
    core::ResourceType resType = static_cast<core::ResourceType>(type);
    double modifier = serialized["miningSpeedModifier"].toDouble();
    return std::make_shared<core::Resource>(resType, amount, modifier);
}

std::optional<std::shared_ptr<core::Attribute>>
utils::Serializer::damagingDeserializer(const QJsonObject& serialized) {
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
utils::Serializer::damageableDeserializer(const QJsonObject& serialized) {
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
utils::Serializer::movingDeserializer(const QJsonObject& serialized) {
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
    ++dirIter;
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

std::optional<std::shared_ptr<core::Attribute>>
utils::Serializer::miningDeserializer(const QJsonObject& serialized) {
    auto object = std::make_shared<core::Mining>();
    if (!serialized["miningSpeed"].isDouble() || !serialized["miningDelay"].isDouble()
        || !serialized["miningRadius"].isDouble()) {
        return std::nullopt;
    }
    object->setMiningSpeed((serialized["miningSpeed"]).toInt());
    object->setMiningDelay((serialized["miningDelay"]).toInt());
    object->setMiningRadius((serialized["miningRadius"]).toDouble());
    object->setMining(serialized["mining"].toBool(false));
    return object;
}


std::optional<QJsonObject> utils::Serializer::gameWorldSerializer(const core::GameWorld& world) {
    QJsonObject json;
    json.insert("width", world.getWidth());
    json.insert("height", world.getHeight());
    QJsonArray resources;
    QJsonObject object;
    QVector<QPair<core::ResourceType, int>> resVector = world.getResources();
    for (auto res : resVector) {
        QJsonObject resPair;
        resPair.insert("type", static_cast<int>(res.first));
        resPair.insert("amount", res.second);
        resources.append(resPair);
    }
    json.insert("resources", resources);
    auto iter = world.getObjects().begin();
    while (iter != world.getObjects().end()) {
        std::optional<QJsonObject> result = objectSerializer(*iter.value());
        if (result == std::nullopt) {
            return result;
        }
        object.insert(QString::number(iter.key()), result.value());
        ++iter;
    }
    json.insert("resources", resources);
    json.insert("objects", object);
    return json;
}

std::optional<core::GameWorld>
utils::Serializer::gameWorldDeserialize(const QJsonObject& serialized) {
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
    QVector<QPair<core::ResourceType, int>> resVector;
    for (const auto& res : resources) {
        if (!res.isObject()) {
            return std::nullopt;
        }
        auto resObj = res.toObject();
        int type = resObj["type"].toInt();
        int amount = resObj["amount"].toInt();
        resVector.push_back(QPair(static_cast<core::ResourceType>(type), amount));
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
        ++iter;
    }
    ans.setObjects(hashObjects);
    return ans;
}

QString utils::Serializer::jsonObjectToString(const QJsonObject& jsonObject) {
    QJsonDocument doc(jsonObject);
    if (isPrettyPrinting()) {
        return doc.toJson(QJsonDocument::Indented);
    }
    return doc.toJson(QJsonDocument::Compact);
}

std::optional<QJsonObject> utils::Serializer::stringToJsonObject(const QString& jsonString) {
    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonString.toUtf8());

    // check validity of the document
    if (jsonDocument.isNull()) {
        return std::nullopt;
    }

    if (!jsonDocument.isObject()) {
        return std::nullopt;
    }

    return jsonDocument.object();
}

std::optional<core::Command> utils::Serializer::commandDeserializer(const QJsonObject& serialized) {
    core::Command command;
    if (!serialized["typeName"].isString()) {
        return std::nullopt;
    }
    command.setName(serialized["typeName"].toString());
    QStringList arguments;
    QJsonArray json;
    if (!serialized["arguments"].isArray()) {
        return std::nullopt;
    }
    json = serialized["arguments"].toArray();
    for (const auto& i : json) {
        if (!i.isString()) {
            return std::nullopt;
        }
        arguments.push_back(i.toString());
    }
    command.setArguments(arguments);
    return command;
}

std::optional<server::ObjectSignature>
utils::Serializer::objectSignatureDeserializer(const QJsonObject& serialized) {
    if (!serialized["typeName"].isString()) {
        return std::nullopt;
    }
    QVector<QPointF> vec;
    if (!serialized["hitbox"].isObject()) {
        return std::nullopt;
    }
    QJsonObject pos;
    pos = serialized["hitbox"].toObject();
    auto iterPos = pos.begin();
    if (!(*iterPos).isArray()) {
        return std::nullopt;
    }
    QJsonArray xArray = (*iterPos).toArray();
    ++iterPos;
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
        vec[it++].setY(qreal(i.toDouble()));
    }
    server::ObjectSignature signature(serialized["typeName"].toString(), QPolygonF(vec));
    QStringList strategies;
    QJsonArray json;
    if (!serialized["strategies"].isArray()) {
        return std::nullopt;
    }
    json = serialized["strategies"].toArray();
    for (const auto& i : json) {
        if (!i.isString()) {
            return std::nullopt;
        }
        strategies.push_back(i.toString());
    }
    signature.setStrategies(strategies);
    if (serialized["objects"].isObject()) {
        return std::nullopt;
    }
    QJsonObject objects = serialized["objects"].toObject();
    QJsonObject attributes;
    if (!serialized["attributes"].isObject()) {
        return std::nullopt;
    }
    attributes = serialized["attributes"].toObject();
    QLinkedList<std::shared_ptr<core::Attribute> > objectAttributes;
    auto iter = attributes.begin();
    while (iter != attributes.end()) {
        if (!iter.value().isObject()) {
            return std::nullopt;
        }
        QJsonObject attribute = iter.value().toObject();
        std::optional<std::shared_ptr<core::Attribute>> result = utils::Factory::getDeserializer(
                iter.key())(attribute);
        if (result == std::nullopt) {
            return std::nullopt;
        }
        objectAttributes.push_back(result.value());
        ++iter;
    }
    signature.setAttributes(objectAttributes);
    return signature;
}

std::optional<QJsonObject>
utils::Serializer::objectSignatureSerializer(const server::ObjectSignature& signature) {
    QJsonObject json;
    json["typeName"] = signature.getTypeName();
    QJsonObject position;
    QPolygonF hitbox = signature.getHitbox();
    int iter = 0;
    QJsonArray xArray, yArray;
    for (const auto& i : hitbox) {
        xArray.push_back(i.x());
        yArray.push_back(i.y());
        ++iter;
    }
    position.insert("x", xArray);
    position.insert("y", yArray);
    json["hitbox"] = position;
    QJsonArray stratigies;
    for (const auto& i : signature.getStrategies()) {
        stratigies.push_back(i);
    }
    json["strategies"] = stratigies;
    QJsonObject attributes;
    for (const auto& attribute : signature.getAttributes()) {
        std::optional<QJsonObject> result = utils::Factory::getSerializer(
                attribute->getAttributeName())(attribute);
        if (result == std::nullopt) {
            return std::nullopt;
        }
        attributes.insert(attribute->getAttributeName(), result.value());
    }
    json["attributes"] = attributes;
    return json;
}


std::optional<QJsonObject> utils::Serializer::commandSerializer(const core::Command& command) {
    QJsonObject json;
    json["typeName"] = command.getName();
    QJsonArray arguments;
    for (const auto& i : command.getArguments()) {
        arguments.push_back(i);
    }
    json["arguments"] = arguments;
    return json;

}

std::optional<QString>
utils::Serializer::serializeObjectSignature(const server::ObjectSignature& signature) {
    auto result = objectSignatureSerializer(signature);
    if (result == std::nullopt) {
        return std::nullopt;
    }
    return jsonObjectToString(result.value());
}

std::optional<QString> utils::Serializer::serializeCommand(const core::Command& command) {
    auto result = commandSerializer(command);
    if (result == std::nullopt) {
        return std::nullopt;
    }
    return jsonObjectToString(result.value());
}

std::optional<server::ObjectSignature>
utils::Serializer::deserializeObjectSignature(const QString& serialized) {
    std::optional<QJsonObject> json = stringToJsonObject(serialized);
    if (json == std::nullopt) {
        return std::nullopt;
    }
    return objectSignatureDeserializer(json.value());
}

std::optional<core::Command> utils::Serializer::deserializeCommand(const QString& serialized) {
    std::optional<QJsonObject> json = stringToJsonObject(serialized);
    if (json == std::nullopt) {
        return std::nullopt;
    }
    return commandDeserializer(json.value());
}

std::optional<QJsonObject>
utils::Serializer::wallSerializer(const std::shared_ptr<core::Attribute>& attribute) {
    auto object = dynamic_cast<core::Wall*>(attribute.get());
    QJsonObject json;
    if (object == nullptr) {
        return std::nullopt;
    }
    if (object->getType() == core::WallType::kWall) {
        json.insert("wallType", 1);
    }
    if (object->getType() == core::WallType::kGate) {
        json.insert("wallType", 2);
    }
    if (object->getType() == core::WallType::kColumn) {
        json.insert("wallType", 3);
    }
    return json;
}

std::optional<QJsonObject>
utils::Serializer::costSerializer(const std::shared_ptr<core::Attribute>& attribute) {
    auto object = dynamic_cast<core::Cost*>(attribute.get());
    QJsonObject json;
    QJsonArray ans;
    if (object == nullptr) {
        return std::nullopt;
    }
    auto iter = object->getCost().begin();
    while (iter != object->getCost().end()) {
        std::optional<QJsonObject> result = resourceSerializer(
                std::make_shared<core::Resource>(*iter));
        if (result == std::nullopt) {
            return result;
        }
        QJsonObject thisObj;
        thisObj.insert("object", result.value());
        ++iter;
        ans.push_back(thisObj);
    }
    json.insert("all", ans);
    return json;
}

std::optional<std::shared_ptr<core::Attribute>>
utils::Serializer::wallDeserializer(const QJsonObject& serialized) {
    if (!serialized["wallType"].isDouble()) {
        return std::nullopt;
    }
    int x = serialized["wallType"].toDouble();
    core::WallType wallType;
    if (x == 1) {
        wallType = core::WallType::kWall;
    }
    if (x == 2) {
        wallType = core::WallType::kGate;
    }
    if (x == 3) {
        wallType = core::WallType::kColumn;
    }
    auto object = new core::Wall(wallType);
    return std::make_shared<core::Wall>(*object);
}

std::optional<std::shared_ptr<core::Attribute>>
utils::Serializer::costDeserializer(const QJsonObject& serialized) {
    if (!serialized["all"].isArray()) {
        return std::nullopt;
    }
    QJsonArray array = serialized["all"].toArray();
    QVector<core::Resource> cost;
    for (const auto obj : array) {
        if (!obj.isObject()) {
            return std::nullopt;
        }
        QJsonObject myObj = obj.toObject();
        if (!myObj["object"].isObject()) {
            return std::nullopt;
        }
        QJsonObject jsonOfObject = myObj["object"].toObject();
        auto res = resourceDeserializer(jsonOfObject);
        if (res == std::nullopt) {
            return std::nullopt;
        }
        cost.push_back(*dynamic_cast<core::Resource*>(res.value().get()));
    }
    auto object = new core::Cost(cost);
    return std::make_shared<core::Cost>(*object);
}
