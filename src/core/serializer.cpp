/*#include "serializer.h"

QString core::Serializer::serialize(const core::Object& object) {
    QString serialized;
    QJsonObject json;
    addJsonObject(object, json);
    convertJsonToString(json, serialized);
    return serialized;
}

QString core::Serializer::serialize(const core::Resource& object) {
    QString serialized;
    QJsonObject json;
    addJsonResource(object, json);
    convertJsonToString(json, serialized);
    return serialized;
}

QString core::Serializer::serialize(const core::Moving& object) {
    QString serialized;
    QJsonObject json;
    addJsonMoving(object, json);
    convertJsonToString(json, serialized);
    return serialized;
}

QString core::Serializer::serialize(const core::GameWorld& object) {
    /* //TODO
      QJsonObject _json;
    _json.insert("height", object.getHeight());
    _json.insert("width", object.getWidth());
    QJsonArray objects_key;
    QMap<int64_t, core::Object*> _map = object.getObjects();
    for (auto i:_map.keys()) {
        objects_key.push_back(i);
    }
    _json.insert("keys", objects_key);
    QJsonArray objects;
    for (auto i:_map) {
        QJsonArray this_object;

    }
    _json.insert("objectPointers",objects);
    QVector<Resource>all_recources=object.getResources();
    QJsonArray resources;
    for(auto i:all_recources){
        QJsonArray this_resource;
        addJsonResource(i,this_resource);
        QJsonArray.push_back(this_resource)''
    }
    _json.insert("resources",resources);
    finish(_json,serialized);*/
/*    return "";
}

QString core::Serializer::serialize(const core::ResourceBundle& object) {
    QString serialized;
    QJsonObject json;
    addJsonObject(object, json);
    addJsonDamageable(object, json);
    if (object.getResourceType() == ResourceType::kWood) {
        json.insert("resourceType", 1);
    }
    if (object.getResourceType() == ResourceType::kIron) {
        json.insert("resourceType", 2);
    }
    if (object.getResourceType() == ResourceType::kStone) {
        json.insert("resourceType", 3);
    }
    convertJsonToString(json, serialized);
    return serialized;
}

QString core::Serializer::serialize(const core::Damaging& object) {
    QString serialized;
    QJsonObject json;
    addJsonDamaging(object, json);
    convertJsonToString(json, serialized);
    return serialized;
}

QString core::Serializer::serialize(const core::Building& object) {
    QString serialized;
    QJsonObject json;
    addJsonObject(object, json);
    addJsonDamageable(object, json);
    convertJsonToString(json, serialized);
    return serialized;
}

QString core::Serializer::serialize(const core::Damageable& object) {
    QString serialized;
    QJsonObject json;
    addJsonDamageable(object, json);
    convertJsonToString(json, serialized);
    return serialized;
}

QString core::Serializer::serialize(const core::Unit& object) {
    QString serialized;
    QJsonObject json;
    addJsonObject(object, json);
    addJsonDamageable(object, json);
    addJsonDamaging(object, json);
    addJsonMoving(object, json);
    convertJsonToString(json, serialized);
    return serialized;
}

bool core::Serializer::deserialize(core::Object& object, const QString& serialized) {
    QJsonObject json;
    bool ok = objectFromString(serialized, json);
    if (!ok) {
        return false;
    }
    ok = buildObject(object, json);
    if (!ok) {
        return false;
    }
    return true;
}

bool core::Serializer::deserialize(core::Resource& object, const QString& serialized) {
    QJsonObject json;
    bool ok = objectFromString(serialized, json);
    if (!ok) {
        return false;
    }
    ok = buildResourse(object, json);
    if (!ok) {
        return false;
    }
    return true;
}

bool core::Serializer::deserialize(core::ResourceBundle& object, const QString& serialized) {
    QJsonObject json;
    bool ok = objectFromString(serialized, json);
    if (!ok) {
        return false;
    }
    ok = buildObject(object, json);
    if (!ok) {
        return false;
    }
    ok = buildDamageable(object, json);
    if (!ok) {
        return false;
    }
    if (!json["resourceType"].isDouble()) {
        return false;
    }
    int data = (json["resourceType"]).toDouble();
    object.setType(static_cast<ResourceType>(data));
    return data >= 1 && data <= 3;
}

bool core::Serializer::deserialize(core::Moving& object, const QString& serialized) {
    QJsonObject json;
    bool ok = objectFromString(serialized, json);
    if (!ok) {
        return false;
    }
    ok = buildMoving(object, json);
    if (!ok) {
        return false;
    }
    return true;
}

bool core::Serializer::deserialize(core::GameWorld& object, const QString& serialized) {
    return false;
}

bool core::Serializer::deserialize(core::Damaging& object, const QString& serialized) {
    QJsonObject json;
    bool ok = objectFromString(serialized, json);
    if (!ok) {
        return false;
    }
    ok = buildDamaging(object, json);
    if (!ok) {
        return false;
    }
    return true;
}

bool core::Serializer::deserialize(core::Building& object, const QString& serialized) {
    QJsonObject json;
    bool ok = objectFromString(serialized, json);
    if (!ok) {
        return false;
    }
    ok = buildObject(object, json);
    if (!ok) {
        return false;
    }
    ok = buildDamageable(object, json);
    if (!ok) {
        return false;
    }
    return true;
}

bool core::Serializer::deserialize(core::Damageable& object, const QString& serialized) {
    QJsonObject json;
    bool ok = objectFromString(serialized, json);
    if (!ok) {
        return false;
    }
    ok = buildDamageable(object, json);
    if (!ok) {
        return false;
    }
    return true;
}

bool core::Serializer::deserialize(core::Unit& object, const QString& serialized) {
    QJsonObject json;
    if (!objectFromString(serialized, json)) {
        return false;
    }
    if (!buildObject(object, json)) {
        return false;
    }
    if (!buildDamageable(object, json)) {
        return false;
    }
    if (!buildDamaging(object, json)) {
        return false;
    }
    return buildMoving(object, json);
}

void core::Serializer::addJsonObject(const core::Object& object, QJsonObject& json) {
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
}

void core::Serializer::addJsonResource(const core::Resource& object, QJsonObject& json) {
    if (object.getType() == ResourceType::kWood) {
        json.insert("resourceType", 1);
    }
    if (object.getType() == ResourceType::kIron) {
        json.insert("resourceType", 2);
    }
    if (object.getType() == ResourceType::kStone) {
        json.insert("resourceType", 3);
    }
    json.insert("amount", object.getAmount());
}

void core::Serializer::addJsonDamaging(const core::Damaging& object, QJsonObject& json) {
    json.insert("damage", object.getDamage());
    json.insert("radius", object.getAttackRadius());
    json.insert("delay", object.getAttackDelay());
    json.insert("bulletType", object.getBulletType());
}

void core::Serializer::addJsonDamageable(const core::Damageable& object, QJsonObject& json) {
    json.insert("health", object.getHealth());
    json.insert("maxHealth", object.getMaxHealth());
}

void core::Serializer::convertJsonToString(const QJsonObject& Object, QString& serialized) {
    QJsonDocument doc(Object);
    QString strJson(doc.toJson(QJsonDocument::Compact));
    serialized = std::move(strJson);
}

void core::Serializer::addJsonMoving(const core::Moving& object, QJsonObject& json) {
    QJsonObject direction;
    direction.insert("x", object.getDirection().x());
    direction.insert("y", object.getDirection().y());
    json.insert("direction", direction);
    json.insert("maxSpeed", object.getMaxSpeed());
    json.insert("speed", object.getSpeed());
}

bool core::Serializer::objectFromString(const QString& in, QJsonObject& json) {
    QJsonDocument doc = QJsonDocument::fromJson(in.toUtf8());
    // check validity of the document
    if (doc.isNull() || !doc.isObject()) {
        return false;
    }
    json = doc.object();
    return true;
}

bool core::Serializer::buildObject(core::Object& object,
                                   const QJsonObject& json) {
    if (!json["id"].isString()) {
        return false;
    }
    QString idStr = json["id"].toString();
    bool ok = false;
    uint64_t id = idStr.toULongLong(&ok);
    if (!ok) {
        return ok;
    }
    object.setId(id);
    QJsonObject pos;
    if (!json["position"].isObject()) {
        return false;
    }
    pos = (json["position"]).toObject();
    auto iterPos = pos.begin();
    if (!(*iterPos).isDouble()) {
        return false;
    }
    double x = (*iterPos).toDouble();
    iterPos++;
    if (!(*iterPos).isDouble()) {
        return false;
    }
    double y = (*iterPos).toDouble();
    iterPos++;
    QPointF point(x, y);
    object.setPosition(point);
    if (!json["rotationAngle"].isDouble()) {
        return false;
    }
    object.setRotationAngle((json["rotationAngle"]).toDouble());
    QVector<QPointF> vec;
    if (!json["hitbox"].isObject()) {
        return false;
    }
    pos = json["hitbox"].toObject();
    iterPos = pos.begin();
    if (!(*iterPos).isArray()) {
        return false;
    }
    QJsonArray xArray = (*iterPos).toArray();
    iterPos++;
    if (!(*iterPos).isArray()) {
        return false;
    }
    QJsonArray yArray = (*iterPos).toArray();
    if (xArray.size() != yArray.size()) {
        return false;
    }
    for (const auto& i : xArray) {
        if (!i.isDouble()) {
            return false;
        }
        vec.push_back(QPointF(i.toDouble(), 0));
    }
    int it = 0;
    for (const auto& i : yArray) {
        if (!i.isDouble()) {
            return false;
        }
        vec[it].setY(qreal(i.toDouble()));
    }
    object.setHitbox(QPolygonF(vec));
    return true;
}

bool core::Serializer::buildResourse(core::Resource& object, const QJsonObject& json) {
    if (!json["amount"].isDouble()) {
        return false;
    }
    int amount = json["amount"].toDouble();
    object.setAmount(amount);

    if (!json["resourceType"].isDouble()) {
        return false;
    }
    int type = json["resourceType"].toDouble();
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

    object.setType(resType);
    return true;
}

bool core::Serializer::buildDamaging(core::Damaging& object, const QJsonObject& json) {
    if (!json["bulletType"].isString()) {
        return false;
    }
    object.setBulletType((json["bulletType"]).toString());

    if (!json["damage"].isDouble()) {
        return false;
    }
    object.setDamage((json["damage"]).toDouble());

    if (!json["delay"].isDouble()) {
        return false;
    }
    object.setAttackDelay((json["delay"]).toDouble());
    if (!json["radius"].isDouble()) {
        return false;
    }
    object.setAttackRadius((json["radius"]).toDouble());
    return true;
}

bool core::Serializer::buildDamageable(core::Damageable& object, const QJsonObject& json) {
    if (!json["health"].isDouble()) {
        return false;
    }
    object.setHealth(json["health"].toDouble());

    if (!json["maxHealth"].isDouble()) {
        return false;
    }
    object.setMaxHealth(json["maxHealth"].toDouble());
    return true;
}

bool core::Serializer::buildMoving(core::Moving& object, const QJsonObject& json) {
    QJsonObject direction;

    if (!json["direction"].isObject()) {
        return false;
    }

    direction = json["direction"].toObject();
    QJsonObject::Iterator dirIter = direction.begin();
    double x, y;
    if (!(dirIter)->isDouble()) {
        return false;
    }

    x = (dirIter)->toDouble();
    dirIter++;
    if (!dirIter->isDouble()) {
        return false;
    }
    y = (dirIter)->toDouble();
    object.setDirection(QVector2D(x, y));
    if (!json["maxSpeed"].isDouble()) {
        return false;
    }
    object.setMaxSpeed(json["maxSpeed"].toDouble());
    if (!json["speed"].isDouble()) {
        return false;
    }
    object.setSpeed(json["speed"].toDouble());
    return true;
}
*/