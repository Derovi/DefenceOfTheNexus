#include <QVector2D>

#include "moving.h"

core::Moving::Moving(): direction(QVector2D()), speed(0), maxSpeed(0) {}

core::Moving::Moving(QVector2D direction, double speed, double maxSpeed):
        direction(direction), speed(speed), maxSpeed(maxSpeed) {}

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
    direction = newDirection;
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
