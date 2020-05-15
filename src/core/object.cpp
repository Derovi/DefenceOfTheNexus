#include <utility>
#include <QtGui/QMatrix>

#include "attribute.h"
#include "object.h"

core::Object::Object(uint64_t id, QString typeName, QPointF position, QPolygonF hitbox,
                     float rotationAngle, int team):
    typeName(std::move(typeName)), hitbox(std::move(hitbox)), position(position), id(id),
    team(team), rotationAngle(rotationAngle) {}

uint64_t core::Object::getId() const {
    return id;
}

QPointF core::Object::getPosition() const {
    return position;
}

QPolygonF core::Object::getHitbox() const {
    return hitbox;
}

float core::Object::getRotationAngle() const {
    return rotationAngle;
}

void core::Object::setPosition(const QPointF& newPosition) {
    position = newPosition;
}

void core::Object::setHitbox(const QPolygonF& newHitbox) {
    hitbox = newHitbox;
}

void core::Object::setRotationAngle(float angle) {
    rotationAngle = angle;
}

void core::Object::setId(uint64_t newId) {
    id = newId;
}

QLinkedList<std::shared_ptr<core::Attribute>>& core::Object::getAttributes() {
    return attributes;
}

void core::Object::setAttributes(const QLinkedList<std::shared_ptr<Attribute>>& attributes) {
    this->attributes = attributes;
}

QStringList& core::Object::getStrategies() {
    return strategies;
}

void core::Object::setStrategies(const QStringList& strategies) {
    this->strategies = strategies;
}

bool core::Object::hasAttribute(const QString& name) const {
    for (const auto& attribute : attributes) {
        if (attribute->getAttributeName() == name) {
            return true;
        }
    }
    return false;
}

const QString& core::Object::getTypeName() const {
    return typeName;
}

void core::Object::setTypeName(const QString& typeName) {
    this->typeName = typeName;
}

const QLinkedList<std::shared_ptr<core::Attribute>>& core::Object::getAttributes() const {
    return attributes;
}

std::shared_ptr<core::Attribute> core::Object::getAttribute(const QString& name) {
    for (const auto& attribute : attributes) {
        if (attribute->getAttributeName() == name) {
            return attribute;
        }
    }
    return nullptr;
}

const QStringList& core::Object::getStrategies() const {
    return strategies;
}

QPolygonF core::Object::getRotatedHitbox() const {
    QMatrix matrix;
    matrix.rotate(rotationAngle);
    return matrix.map(getHitbox());
}

bool core::Object::isIntersect(const QPointF& point) const {
    return getHitboxOnMap().contains(point);
}

bool core::Object::isIntersect(const QRectF& rect) const {
    return getHitboxOnMap().intersects(QPolygonF(rect));
}

bool core::Object::isIntersect(const QPolygonF& polygon) const {
    return getHitboxOnMap().intersects(polygon);
}

bool core::Object::isIntersect(const core::Object& object) const {
    return object.getHitboxOnMap().intersects(getHitboxOnMap());
}

QPolygonF core::Object::getHitboxOnMap() const {
    auto hitboxOnMap = getRotatedHitbox();
    hitboxOnMap.translate(getPosition());
    return hitboxOnMap;
}

uint8_t core::Object::getTeam() const {
    return team;
}

void core::Object::setTeam(uint8_t team) {
    Object::team = team;
}
