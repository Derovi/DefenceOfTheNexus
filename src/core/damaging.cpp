#include <utility>

#include <QString>

#include "damaging.h"

core::Damaging::Damaging(): damage(0), attackDelay(0), attackRadius(0) {}

core::Damaging::Damaging(int damage, double attackRadius, double attackDelay,
                         QString bulletType):
        damage(damage), attackRadius(attackRadius), attackDelay(attackDelay),
        bulletType(std::move(bulletType)) {}

int core::Damaging::getDamage() const {
    return damage;
}

double core::Damaging::getAttackRadius() const {
    return attackRadius;
}

double core::Damaging::getAttackDelay() const {
    return attackDelay;
}

void core::Damaging::setAttackRadius(double radius) {
    attackRadius = radius;
}

void core::Damaging::setAttackDelay(double delay) {
    attackDelay = delay;
}

void core::Damaging::setDamage(int newDamage) {
    damage = newDamage;
}

void core::Damaging::set(const core::Damaging& properties) {
    setDamage(properties.damage);
    setAttackDelay(properties.attackDelay);
    setAttackRadius(properties.attackRadius);
}
