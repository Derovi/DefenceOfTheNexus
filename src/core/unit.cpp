#include <utility>

#include "unit.h"

core::Unit::Unit(uint64_t id, QPointF position, QPolygonF hitbox, float rotationAngle,
                 const core::Moving& movingProperties, const core::Damaging& damagingProperties,
                 const core::Damageable& damageableProperties):
        Object(id, position, std::move(hitbox), rotationAngle),
        Moving(movingProperties),
        Damaging(damagingProperties),
        Damageable(damageableProperties) {}

QString core::Unit::getTypeName() {
    return typeName;
}

QString core::Unit::typeName = "unit";
