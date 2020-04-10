#include <utility>

#include "unit.h"

core::Unit::Unit(uint64_t id, QPointF position, QPolygonF hitbox, float rotationAngle,
                 const core::Moving& movingProperties, const core::Damaging& damagingProperties,
                 const core::Damageable& damageableProperties):
        Object(id, position, std::move(hitbox), rotationAngle),
        moving(movingProperties),
        damaging(damagingProperties),
        damageable(damageableProperties) {}

QString core::Unit::getTypeName() {
    return typeName;
}

QString core::Unit::typeName = "unit";

core::Moving& core::Unit::getMoving() {
    return moving;
}

void core::Unit::setMoving(const core::Moving& moving) {
    Unit::moving = moving;
}

core::Damaging& core::Unit::getDamaging() {
    return damaging;
}

void core::Unit::setDamaging(const core::Damaging& damaging) {
    Unit::damaging = damaging;
}

core::Damageable& core::Unit::getDamageable() {
    return damageable;
}

void core::Unit::setDamageable(const core::Damageable& damageable) {
    Unit::damageable = damageable;
}
