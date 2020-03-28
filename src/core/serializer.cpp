//
// Created by ok-PC on 24.03.2020.
//

#include "serializer.h"


void core::Serializer::serialize(const core::Object& object, QString& serialized) {
    QJsonObject my_json;
    addJsonObject(object, my_json);
    finish(my_json, serialized);
}

void core::Serializer::serialize(const core::Resource& object, QString& serialized) {
    QJsonObject my_json;
    addJsonResource(object, my_json);
    finish(my_json, serialized);
}

void core::Serializer::serialize(const core::Moving& object, QString& serialized) {
    QJsonObject my_json;
    addJsonMoving(object, my_json);
    finish(my_json, serialized);
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
    QJsonObject my_json;
    addJsonObject(object, my_json);
    addJsonDamageable(object, my_json);
    if (object.getResourceType() == ResourceType::kWood) {
        my_json.insert("resourceType", "wood");
    }
    if (object.getResourceType() == ResourceType::kIron) {
        my_json.insert("resourceType", "iron");
    }
    if (object.getResourceType() == ResourceType::kStone) {
        my_json.insert("resourceType", "stone");
    }
    finish(my_json, serialized);
}

void core::Serializer::serialize(const core::Damaging& object, QString& serialized) {
    QJsonObject my_json;
    addJsonDamaging(object, my_json);
    finish(my_json, serialized);
}

void core::Serializer::serialize(const core::Building& object, QString& serialized) {
    QJsonObject my_json;
    addJsonObject(object, my_json);
    addJsonDamageable(object, my_json);
    finish(my_json, serialized);
}

void core::Serializer::serialize(const core::Damageable& object, QString& serialized) {
    QJsonObject my_json;
    addJsonDamageable(object, my_json);
    finish(my_json, serialized);
}

void core::Serializer::serialize(const core::Unit& object, QString& serialized) {
    QJsonObject my_json;
    addJsonObject(object, my_json);
    addJsonDamageable(object, my_json);
    addJsonDamaging(object, my_json);
    addJsonMoving(object, my_json);
    finish(my_json, serialized);
}

bool core::Serializer::deserialize(core::Object& object, const QString& serialized) {
    QJsonObject my_json;
    bool ok = objectFromString(serialized, my_json);
    if (!ok) {
        return false;
    }
    QJsonObject::Iterator it = my_json.begin();
    ok = buildObject(object, it);
    if (!ok) {
        return false;
    }
    return true;

}

bool core::Serializer::deserialize(core::Resource& object, const QString& serialized) {
    QJsonObject my_json;
    bool ok = objectFromString(serialized, my_json);
    if (!ok) {
        return false;
    }
    QJsonObject::Iterator it = my_json.begin();
    ok = buildResourse(object, it);
    if (!ok) {
        return false;
    }
    return true;
}

bool core::Serializer::deserialize(core::ResourceBundle& object, const QString& serialized) {
    QJsonObject my_json;
    bool ok = objectFromString(serialized, my_json);
    if (!ok) {
        return false;
    }
    QJsonObject::Iterator it = my_json.begin();
    ok = buildObject(object, it);
    if (!ok) {
        return false;
    }
    ok = buildDamageable(object, it);
    if (!ok) {
        return false;
    }
    if (!(*it).isString()) {
        return false;
    }
    QString my_data = (*it).toString();
    if (my_data == "wood") {
        object.setType(ResourceType::kWood);
    }
    if (my_data == "iron") {
        object.setType(ResourceType::kIron);
    }
    if (my_data == "stone") {
        object.setType(ResourceType::kStone);
    }
    return !(my_data != "wood" && my_data != "iron" && my_data != "stone");
}

bool core::Serializer::deserialize(core::Moving& object, const QString& serialized) {
    QJsonObject my_json;
    bool ok = objectFromString(serialized, my_json);
    if (!ok) {
        return false;
    }
    QJsonObject::Iterator it = my_json.begin();
    ok = buildMoving(object, it);
    if (!ok) {
        return false;
    }
    return true;
}

bool core::Serializer::deserialize(core::GameWorld& object, const QString& serialized) {
    return false;
}

bool core::Serializer::deserialize(core::Damaging& object, const QString& serialized) {
    QJsonObject my_json;
    bool ok = objectFromString(serialized, my_json);
    if (!ok) {
        return false;
    }
    QJsonObject::Iterator it = my_json.begin();
    ok = buildDamaging(object, it);
    if (!ok) {
        return false;
    }
    return true;
}

bool core::Serializer::deserialize(core::Building& object, const QString& serialized) {
    QJsonObject my_json;
    bool ok = objectFromString(serialized, my_json);
    if (!ok) {
        return false;
    }
    QJsonObject::Iterator it = my_json.begin();
    ok = buildObject(object, it);
    if (!ok) {
        return false;
    }
    ok = buildDamageable(object, it);
    if (!ok) {
        return false;
    }
    return true;
}

bool core::Serializer::deserialize(core::Damageable& object, const QString& serialized) {
    QJsonObject my_json;
    bool ok = objectFromString(serialized, my_json);
    if (!ok) {
        return false;
    }
    QJsonObject::Iterator it = my_json.begin();
    ok = buildDamageable(object, it);
    if (!ok) {
        return false;
    }
    return true;
}

bool core::Serializer::deserialize(core::Unit& object, const QString& serialized) {
    QJsonObject my_json;
    bool ok = objectFromString(serialized, my_json);
    if (!ok) {
        return false;
    }
    QJsonObject::Iterator it = my_json.begin();
    ok = buildObject(object, it);
    if (!ok) {
        return false;
    }
    ok = buildDamageable(object, it);

    if (!ok) {
        return false;
    }

    ok = buildDamaging(object, it);
    if (!ok) {
        return false;
    }
    ok = buildMoving(object, it);
    if (!ok) {
        return false;
    }
    return true;
}

void core::Serializer::addJsonObject(const core::Object& object, QJsonObject& my_json) {
    QJsonObject polygon, pos;
    my_json.insert("1id", QString::number(object.getId()));
    pos.insert("x", object.getPosition().x());
    pos.insert("y", object.getPosition().y());
    my_json.insert("1position", pos);
    my_json.insert("1rotationAngle", object.getRotationAngle());
    QVector<QPointF> my_rectangle;
    QPolygonF hitbox = object.getHitbox();
    int iter = 0;
    QJsonArray x_array, y_array;

    for (auto i:hitbox) {
        x_array.push_back(i.x());
        y_array.push_back(i.y());
        iter++;
    }
    pos.remove("x");
    pos.remove("y");
    pos.insert("x", x_array);
    pos.insert("y", y_array);
    my_json.insert("1hitbox", pos);
}

void core::Serializer::addJsonResource(const core::Resource& object, QJsonObject& my_json) {
    if (object.getType() == ResourceType::kWood) {
        my_json.insert("resourceType", "wood");
    }
    if (object.getType() == ResourceType::kIron) {
        my_json.insert("resourceType", "iron");
    }
    if (object.getType() == ResourceType::kStone) {
        my_json.insert("resourceType", "stone");
    }
    my_json.insert("amount", object.getAmount());
}

void core::Serializer::addJsonDamaging(const core::Damaging& object, QJsonObject& my_json) {
    my_json.insert("3damage", object.getDamage());
    my_json.insert("3radius", object.getAttackRadius());
    my_json.insert("3delay", object.getAttackDelay());
    my_json.insert("3bulletType", object.getBulletType());
}

void core::Serializer::addJsonDamageable(const core::Damageable& object, QJsonObject& my_json) {
    my_json.insert("2health", object.getHealth());
    my_json.insert("2maxHealth", object.getMaxHealth());
}

void core::Serializer::finish(const QJsonObject& my_object, QString& serialized) {
    QJsonDocument doc(my_object);
    QString strJson(doc.toJson(QJsonDocument::Compact));
    serialized = strJson;
}

void core::Serializer::addJsonMoving(const core::Moving& object, QJsonObject& my_json) {
    QJsonObject direction;
    direction.insert("x", object.getDirection().x());
    direction.insert("y", object.getDirection().y());
    my_json.insert("4direction", direction);
    my_json.insert("4maxSpeed", object.getMaxSpeed());
    my_json.insert("4speed", object.getSpeed());
}

bool core::Serializer::objectFromString(const QString& in, QJsonObject& my_json) {
    QJsonDocument doc = QJsonDocument::fromJson(in.toUtf8());
    // check validity of the document
    if (!doc.isNull()) {
        if (doc.isObject()) {
            my_json = doc.object();
        } else {
            return false;
        }
    } else {
        return false;
    }
    return true;
}

bool core::Serializer::buildObject(core::Object& object,
                                   QJsonObject::iterator& iter) {
    iter++;
    if (!(*iter).isString()) {
        return false;
    }
    QString id_str = (*iter).toString();
    bool ok = false;
    uint64_t id = id_str.toULongLong(&ok);
    if (!ok) {
        return ok;
    }
    object.setId(id);
    iter++;
    QJsonObject pos;
    if (!(*iter).isObject()) {
        return false;
    }
    pos = (*iter).toObject();
    auto iter_pos = pos.begin();
    if (!(*iter_pos).isDouble()) {
        return false;
    }
    double x = (*iter_pos).toDouble();
    iter_pos++;
    if (!(*iter_pos).isDouble()) {
        return false;
    }
    double y = (*iter_pos).toDouble();
    iter_pos++;
    QPointF my_point(x, y);
    object.setPosition(my_point);
    iter++;
    if (!(*iter).isDouble()) {
        return false;
    }
    object.setRotationAngle((*iter).toDouble());
    iter--;
    iter--;
    iter--;
    QVector<QPointF> my_vec;
    if (!(*iter).isObject()) {
        return false;
    }
    pos = (*iter).toObject();
    iter++;
    iter++;
    iter++;
    iter++;
    iter_pos = pos.begin();
    if (!(*iter_pos).isArray()) {
        return false;
    }
    QJsonArray x_array = (*iter_pos).toArray();
    iter_pos++;
    if (!(*iter_pos).isArray()) {
        return false;
    }
    QJsonArray y_array = (*iter_pos).toArray();
    if (x_array.size() != y_array.size()) {
        return false;
    }
    for (auto i:x_array) {
        if (!i.isDouble()) {
            return false;
        }
        my_vec.push_back(QPointF(i.toDouble(), 0));
    }
    int it = 0;
    for (auto i:y_array) {
        if (!i.isDouble()) {
            return false;
        }
        my_vec[it].setY(qreal(i.toDouble()));
    }
    object.setHitbox(QPolygonF(my_vec));
    return true;
}

bool core::Serializer::buildResourse(core::Resource& object, QJsonObject::iterator& iter) {
    if (!(*iter).isDouble()) {
        return false;
    }
    int amount = (*iter).toDouble();
    object.setAmount(amount);
    iter++;
    if (!(*iter).isString()) {
        return false;
    }
    QString type = (*iter).toString();
    ResourceType my_type;
    if (type == "wood") {
        my_type = ResourceType::kWood;
    }
    if (type == "iron") {
        my_type = ResourceType::kIron;
    }
    if (type == "stone") {
        my_type = ResourceType::kStone;
    }
    iter++;

    object.setType(my_type);
    return true;
}

bool core::Serializer::buildDamaging(core::Damaging& object, QJsonObject::Iterator& iter) {
    if (!(*iter).isString()) {
        return false;
    }
    object.setBulletType((*iter).toString());
    iter++;
    if (!(*iter).isDouble()) {
        return false;
    }
    object.setDamage((*iter).toDouble());
    iter++;
    if (!(*iter).isDouble()) {
        return false;
    }
    object.setAttackDelay((*iter).toDouble());
    iter++;
    if (!(*iter).isDouble()) {
        return false;
    }
    object.setAttackRadius((*iter).toDouble());

    iter++;
    return true;
}

bool core::Serializer::buildDamageable(core::Damageable& object, QJsonObject::Iterator& iter) {
    if (!(*iter).isDouble()) {
        return false;
    }
    object.setHealth((*iter).toDouble());
    iter++;
    if (!(*iter).isDouble()) {
        return false;
    }
    object.setMaxHealth((*iter).toDouble());
    iter++;
    return true;
}

bool core::Serializer::buildMoving(core::Moving& object, QJsonObject::Iterator& iter) {
    QJsonObject direction;

    if (!(*iter).isObject()) {
        return false;
    }

    direction = (*iter).toObject();
    QJsonObject::Iterator dir_iter = direction.begin();
    double x, y;
    if (!(dir_iter)->isDouble()) {
        return false;
    }

    x = (dir_iter)->toDouble();
    dir_iter++;
    if (!dir_iter->isDouble()) {
        return false;
    }
    y = (dir_iter)->toDouble();
    object.setDirection(QVector2D(x, y));
    iter++;
    if (!(*iter).isDouble()) {
        return false;
    }
    object.setMaxSpeed((*iter).toDouble());
    iter++;
    if (!(*iter).isDouble()) {
        return false;
    }
    object.setSpeed((*iter).toDouble());
    iter++;
    return true;
}
