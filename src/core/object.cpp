#include <utility>

#include "object.h"

core::Object::Object(uint64_t id, QPointF position, QPolygonF hitbox, float rotationAngle):
        id(id), position(position), hitbox(std::move(hitbox)), rotationAngle(rotationAngle) {}

uint64_t core::Object::getId() const {
    return id;
}

QPointF core::Object::getPosition() const {
    return position;
}

const QPolygonF& core::Object::getHitbox() const {
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

bool core::Object::isIntersect(const core::Object& object) const {
    return object.hitbox.intersects(hitbox);
}

void core::Object::setId(uint64_t newId) {
    *const_cast<uint64_t*>(&id) = newId;
}

