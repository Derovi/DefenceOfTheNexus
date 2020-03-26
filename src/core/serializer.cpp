//
// Created by ok-PC on 24.03.2020.
//

#include "serializer.h"


void core::Serializer::serialize(const core::Object& object, QString& serialized) {
    QJsonObject my_json, pos, polygon;
    my_json.insert("id", QString::number(object.getId()));
    pos.insert("x_cord", QString::number(object.getPosition().x()));
    pos.insert("y_cord", QString::number(object.getPosition().y()));
    my_json.insert("position", pos);
    my_json.insert("rotation angle", QString::number(object.getRotationAngle()));
    QVector<QPointF> my_rectangle;
    QPolygonF hitbox = object.getHitbox();
    int iter = 0;
    for (auto i:hitbox) {
        pos.insert("x_cord of " + QString::number(iter) + " point", QString::number(i.x()));
        pos.insert("y_cord of " + QString::number(iter) + "point", QString::number(i.y()));
        iter++;
    }
    my_json.insert("hitbox", pos);
    QJsonDocument doc(my_json);
    QString strJson(doc.toJson(QJsonDocument::Compact));
    serialized=strJson;
}

void core::Serializer::serialize(const core::Resource& object, QString& serialized) {
    QJsonObject my_json;
    if(object.getType()==ResourceType::kWood) {
        my_json.insert("resource type", "wood");
    }
    if(object.getType()==ResourceType::kIron) {
        my_json.insert("resource type", "iron");
    }
    if(object.getType()==ResourceType::kStone) {
        my_json.insert("resource type", "stone");
    }
    my_json.insert("amount",object.getAmount());
    QJsonDocument doc(my_json);
    QString strJson(doc.toJson(QJsonDocument::Compact));
    serialized=strJson;
}

void core::Serializer::serialize(const core::Moving& object, QString& serialized) {
    QJsonObject my_json,direction;
    direction.insert("x_cord",object.getDirection().x());
    direction.insert("y_cord",object.getDirection().y());
    my_json.insert("direction",direction);
    my_json.insert("max speed",object.getMaxSpeed());
    my_json.insert("speed",object.getSpeed());
    QJsonDocument doc(my_json);
    QString strJson(doc.toJson(QJsonDocument::Compact));
    serialized=strJson;
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

void core::Serializer::serialize(const core::Unit& object, QString& serialized) {

}

bool core::Serializer::deserialize(const core::Unit& object, const QString& serialized) {
    return false;
}
