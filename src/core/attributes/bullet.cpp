#include "bullet.h"

namespace core {

Bullet::Bullet(): damage(0), range(0), ownerId(~0ull), shooterPos(0, 0) {}

QString Bullet::getAttributeName() {
    return attributeName;
}

std::shared_ptr<Attribute> Bullet::clone() {
    return std::make_shared<Bullet>(*this);
}

int Bullet::getDamage() const {
    return damage;
}

double Bullet::getRange() const {
    return range;
}

uint64_t Bullet::getOwnerId() const {
    return ownerId;
}

QPointF Bullet::getShooterPos() const {
    return shooterPos;
}

void Bullet::setDamage(int damage) {
    this->damage = damage;
}

void Bullet::setRange(double range) {
    this->range = range;
}

void Bullet::setOwnerId(uint64_t id) {
    ownerId = id;
}

void Bullet::setShooterPos(QPointF pos) {
    shooterPos = pos;
}

void Bullet::setOwner(std::shared_ptr<core::Object> shooter) {
    ownerId = shooter->getId();
    shooterPos = shooter->getPosition();
}

bool Bullet::operator==(const Bullet& bullet) const {
    return damage == bullet.damage && ownerId == bullet.ownerId
        && qFuzzyIsNull(range - bullet.range) && (shooterPos - bullet.shooterPos).isNull();
}

}  // namespace core
