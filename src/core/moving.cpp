#include <QVector2D>

#include "moving.h"

core::Moving::Moving(): direction(QVector2D()), speed(0), maxSpeed(0) {}

core::Moving::Moving(QVector2D direction, double speed, double maxSpeed):
        direction(direction.normalized()), speed(speed), maxSpeed(maxSpeed) {}

const QVector2D& core::Moving::getDirection() const {
    return direction;
}

double core::Moving::getSpeed() const {
    return speed;
}

double core::Moving::getMaxSpeed() const {
    return maxSpeed;
}

void core::Moving::setDirection(const QVector2D& newDirection) {
    direction = newDirection.normalized();
}

void core::Moving::setSpeed(double newSpeed) {
    speed = newSpeed;
}

void core::Moving::setMaxSpeed(double newMaxSpeed) {
    maxSpeed = newMaxSpeed;
}

void core::Moving::set(const core::Moving& properties) {
    setDirection(properties.direction);
    setSpeed(properties.speed);
    setMaxSpeed(properties.maxSpeed);
}

QString core::Moving::getAttributeName() {
    return attributeName;
}

QString core::Moving::attributeName = "moving";

std::shared_ptr<core::Attribute> core::Moving::clone() {
    return std::shared_ptr<Attribute>(new Moving(*this));
}

