#include "damageable.h"

core::Damageable::Damageable(): health(0), maxHealth(0) {}

core::Damageable::Damageable(int health, int maxHealth): health(health), maxHealth(maxHealth) {}

int core::Damageable::getHealth() const {
    return health;
}

int core::Damageable::getMaxHealth() const {
    return maxHealth;
}

void core::Damageable::setMaxHealth(int newMaxHealth) {
    maxHealth = newMaxHealth;
}

void core::Damageable::setHealth(int newHealth) {
    health = newHealth;
}

void core::Damageable::set(const core::Damageable& properties) {
    setHealth(properties.health);
    setMaxHealth(properties.maxHealth);
}

QString core::Damageable::getAttributeName() {
    return attributeName;
}

std::shared_ptr<core::Attribute> core::Damageable::clone() {
    return std::make_shared<core::Damageable>(*this);
}

bool core::Damageable::operator==(core::Damageable object) {
    return health == object.health && maxHealth == object.maxHealth;
}
