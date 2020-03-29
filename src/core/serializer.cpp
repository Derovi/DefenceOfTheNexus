
#include "serializer.h"


void core::Serializer::serialize(const core::Object& object, QString& serialized) {
    QJsonObject myJson;
    addJsonObject(object, myJson);
    finish(myJson, serialized);
}

void core::Serializer::serialize(const core::Resource& object, QString& serialized) {
    QJsonObject myJson;
    addJsonResource(object, myJson);
    finish(myJson, serialized);
}

void core::Serializer::serialize(const core::Moving& object, QString& serialized) {
    QJsonObject myJson;
    addJsonMoving(object, myJson);
    finish(myJson, serialized);
}

void core::Serializer::serialize(const core::GameWorld& object, QString& serialized) {
    /*QJsonObject my_json;
    my_json.insert("height", object.getHeight());
    my_json.insert("width", object.getWidth());
    QJsonArray objects_key;
    QMap<int64_t, core::Object*> my_map = object.getObjects();
    for (auto i:my_map.keys()) {
        objects_key.push_back(i);
    }
    my_json.insert("keys", objects_key);
    QJsonArray objects;
    for (auto i:my_map) {
        QJsonArray this_object;

    }
    my_json.insert("objectPointers",objects);
    QVector<Resource>all_recources=object.getResources();
    QJsonArray resources;
    for(auto i:all_recources){
        QJsonArray this_resource;
        addJsonResource(i,this_resource);
        QJsonArray.push_back(this_resource)''
    }
    my_json.insert("resources",resources);
    finish(my_json,serialized);*/
}

void core::Serializer::serialize(const core::ResourceBundle& object, QString& serialized) {
    QJsonObject myJson;
    addJsonObject(object, myJson);
    addJsonDamageable(object, myJson);
    if (object.getResourceType() == ResourceType::kWood) {
        myJson.insert("resourceType", "wood");
    }
    if (object.getResourceType() == ResourceType::kIron) {
        myJson.insert("resourceType", "iron");
    }
    if (object.getResourceType() == ResourceType::kStone) {
        myJson.insert("resourceType", "stone");
    }
    finish(myJson, serialized);
}

void core::Serializer::serialize(const core::Damaging& object, QString& serialized) {
    QJsonObject myJson;
    addJsonDamaging(object, myJson);
    finish(myJson, serialized);
}

void core::Serializer::serialize(const core::Building& object, QString& serialized) {
    QJsonObject myJson;
    addJsonObject(object, myJson);
    addJsonDamageable(object, myJson);
    finish(myJson, serialized);
}

void core::Serializer::serialize(const core::Damageable& object, QString& serialized) {
    QJsonObject myJson;
    addJsonDamageable(object, myJson);
    finish(myJson, serialized);
}

void core::Serializer::serialize(const core::Unit& object, QString& serialized) {
    QJsonObject myJson;
    addJsonObject(object, myJson);
    addJsonDamageable(object, myJson);
    addJsonDamaging(object, myJson);
    addJsonMoving(object, myJson);
    finish(myJson, serialized);
}

bool core::Serializer::deserialize(core::Object& object, const QString& serialized) {
    QJsonObject myJson;
    bool ok = objectFromString(serialized, myJson);
    if (!ok) {
        return false;
    }
    ok = buildObject(object, myJson);
    if (!ok) {
        return false;
    }
    return true;
}

bool core::Serializer::deserialize(core::Resource& object, const QString& serialized) {
    QJsonObject myJson;
    bool ok = objectFromString(serialized, myJson);
    if (!ok) {
        return false;
    }
    ok = buildResourse(object, myJson);
    if (!ok) {
        return false;
    }
    return true;
}

bool core::Serializer::deserialize(core::ResourceBundle& object, const QString& serialized) {
    QJsonObject myJson;
    bool ok = objectFromString(serialized, myJson);
    if (!ok) {
        return false;
    }
    ok = buildObject(object, myJson);
    if (!ok) {
        return false;
    }
    ok = buildDamageable(object, myJson);
    if (!ok) {
        return false;
    }
    if (!myJson["resourceType"].isString()) {
        return false;
    }
    QString myData = (myJson["resourceType"]).toString();
    if (myData == "wood") {
        object.setType(ResourceType::kWood);
    }
    if (myData == "iron") {
        object.setType(ResourceType::kIron);
    }
    if (myData == "stone") {
        object.setType(ResourceType::kStone);
    }
    return !(myData != "wood" && myData != "iron" && myData != "stone");
}

bool core::Serializer::deserialize(core::Moving& object, const QString& serialized) {
    QJsonObject myJson;
    bool ok = objectFromString(serialized, myJson);
    if (!ok) {
        return false;
    }
    ok = buildMoving(object, myJson);
    if (!ok) {
        return false;
    }
    return true;
}

bool core::Serializer::deserialize(core::GameWorld& object, const QString& serialized) {
    return false;
}

bool core::Serializer::deserialize(core::Damaging& object, const QString& serialized) {
    QJsonObject myJson;
    bool ok = objectFromString(serialized, myJson);
    if (!ok) {
        return false;
    }
    ok = buildDamaging(object, myJson);
    if (!ok) {
        return false;
    }
    return true;
}

bool core::Serializer::deserialize(core::Building& object, const QString& serialized) {
    QJsonObject myJson;
    bool ok = objectFromString(serialized, myJson);
    if (!ok) {
        return false;
    }
    ok = buildObject(object, myJson);
    if (!ok) {
        return false;
    }
    ok = buildDamageable(object, myJson);
    if (!ok) {
        return false;
    }
    return true;
}

bool core::Serializer::deserialize(core::Damageable& object, const QString& serialized) {
    QJsonObject myJson;
    bool ok = objectFromString(serialized, myJson);
    if (!ok) {
        return false;
    }
    ok = buildDamageable(object, myJson);
    if (!ok) {
        return false;
    }
    return true;
}

bool core::Serializer::deserialize(core::Unit& object, const QString& serialized) {
    QJsonObject myJson;
    bool ok = objectFromString(serialized, myJson);
    if (!ok) {
        return false;
    }
    ok = buildObject(object, myJson);
    if (!ok) {
        return false;
    }
    ok = buildDamageable(object, myJson);
    if (!ok) {
        return false;
    }
    ok = buildDamaging(object, myJson);
    if (!ok) {
        return false;
    }
    ok = buildMoving(object, myJson);
    if (!ok) {
        return false;
    }
    return true;
}

void core::Serializer::addJsonObject(const core::Object& object, QJsonObject& myJson) {
    QJsonObject polygon;
    QJsonObject position;
    myJson.insert("id", QString::number(object.getId()));
    position.insert("x", object.getPosition().x());
    position.insert("y", object.getPosition().y());
    myJson.insert("position", position);
    myJson.insert("rotationAngle", object.getRotationAngle());
    QVector<QPointF> myRectangle;
    QPolygonF hitbox = object.getHitbox();
    int iter = 0;
    QJsonArray xArray, yArray;
    for (auto i:hitbox) {
        xArray.push_back(i.x());
        yArray.push_back(i.y());
        iter++;
    }
    position.remove("x");
    position.remove("y");
    position.insert("x", xArray);
    position.insert("y", yArray);
    myJson.insert("hitbox", position);
}

void core::Serializer::addJsonResource(const core::Resource& object, QJsonObject& myJson) {
    if (object.getType() == ResourceType::kWood) {
        myJson.insert("resourceType", "wood");
    }
    if (object.getType() == ResourceType::kIron) {
        myJson.insert("resourceType", "iron");
    }
    if (object.getType() == ResourceType::kStone) {
        myJson.insert("resourceType", "stone");
    }
    myJson.insert("amount", object.getAmount());
}

void core::Serializer::addJsonDamaging(const core::Damaging& object, QJsonObject& myJson) {
    myJson.insert("damage", object.getDamage());
    myJson.insert("radius", object.getAttackRadius());
    myJson.insert("delay", object.getAttackDelay());
    myJson.insert("bulletType", object.getBulletType());
}

void core::Serializer::addJsonDamageable(const core::Damageable& object, QJsonObject& myJson) {
    myJson.insert("health", object.getHealth());
    myJson.insert("maxHealth", object.getMaxHealth());
}

void core::Serializer::finish(const QJsonObject& myObject, QString& serialized) {
    QJsonDocument doc(myObject);
    QString strJson(doc.toJson(QJsonDocument::Compact));
    serialized = std::move(strJson);
}

void core::Serializer::addJsonMoving(const core::Moving& object, QJsonObject& myJson) {
    QJsonObject direction;
    direction.insert("x", object.getDirection().x());
    direction.insert("y", object.getDirection().y());
    myJson.insert("direction", direction);
    myJson.insert("maxSpeed", object.getMaxSpeed());
    myJson.insert("speed", object.getSpeed());
}

bool core::Serializer::objectFromString(const QString& in, QJsonObject& myJson) {
    QJsonDocument doc = QJsonDocument::fromJson(in.toUtf8());
    // check validity of the document
    if (!doc.isNull()) {
        if (doc.isObject()) {
            myJson = doc.object();
        } else {
            return false;
        }
    } else {
        return false;
    }
    return true;
}

bool core::Serializer::buildObject(core::Object& object,
                                   const QJsonObject& myJson) {
    if (!myJson["id"].isString()) {
        return false;
    }
    QString idStr = myJson["id"].toString();
    bool ok = false;
    uint64_t id = idStr.toULongLong(&ok);
    if (!ok) {
        return ok;
    }
    object.setId(id);
    QJsonObject pos;
    if (!myJson["position"].isObject()) {
        return false;
    }
    pos = (myJson["position"]).toObject();
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
    QPointF myPoint(x, y);
    object.setPosition(myPoint);

    if (!myJson["rotationAngle"].isDouble()) {
        return false;
    }
    object.setRotationAngle((myJson["rotationAngle"]).toDouble());
    QVector<QPointF> myVec;
    if (!myJson["hitbox"].isObject()) {
        return false;
    }
    pos = myJson["hitbox"].toObject();
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
    for (auto i:xArray) {
        if (!i.isDouble()) {
            return false;
        }
        myVec.push_back(QPointF(i.toDouble(), 0));
    }
    int it = 0;
    for (auto i:yArray) {
        if (!i.isDouble()) {
            return false;
        }
        myVec[it].setY(qreal(i.toDouble()));
    }
    object.setHitbox(QPolygonF(myVec));
    return true;
}

bool core::Serializer::buildResourse(core::Resource& object, const QJsonObject& myJson) {
    if (!myJson["amount"].isDouble()) {
        return false;
    }
    int amount = myJson["amount"].toDouble();
    object.setAmount(amount);

    if (!myJson["resourceType"].isString()) {
        return false;
    }
    QString type = myJson["resourceType"].toString();
    ResourceType myType;
    if (type == "wood") {
        myType = ResourceType::kWood;
    }
    if (type == "iron") {
        myType = ResourceType::kIron;
    }
    if (type == "stone") {
        myType = ResourceType::kStone;
    }

    object.setType(myType);
    return true;
}

bool core::Serializer::buildDamaging(core::Damaging& object, const QJsonObject& myJson) {
    if (!myJson["bulletType"].isString()) {
        return false;
    }
    object.setBulletType((myJson["bulletType"]).toString());

    if (!myJson["damage"].isDouble()) {
        return false;
    }
    object.setDamage((myJson["damage"]).toDouble());

    if (!myJson["delay"].isDouble()) {
        return false;
    }
    object.setAttackDelay((myJson["delay"]).toDouble());
    if (!myJson["radius"].isDouble()) {
        return false;
    }
    object.setAttackRadius((myJson["radius"]).toDouble());
    return true;
}

bool core::Serializer::buildDamageable(core::Damageable& object, const QJsonObject& myJson) {
    if (!myJson["health"].isDouble()) {
        return false;
    }
    object.setHealth(myJson["health"].toDouble());

    if (!myJson["maxHealth"].isDouble()) {
        return false;
    }
    object.setMaxHealth(myJson["maxHealth"].toDouble());
    return true;
}

bool core::Serializer::buildMoving(core::Moving& object, const QJsonObject& myJson) {
    QJsonObject direction;

    if (!myJson["direction"].isObject()) {
        return false;
    }

    direction = myJson["direction"].toObject();
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
    if (!myJson["maxSpeed"].isDouble()) {
        return false;
    }
    object.setMaxSpeed(myJson["maxSpeed"].toDouble());
    if (!myJson["speed"].isDouble()) {
        return false;
    }
    object.setSpeed(myJson["speed"].toDouble());
    return true;
}
