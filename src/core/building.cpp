#include <utility>

#include "building.h"

core::Building::Building(uint64_t id, QPointF position, QPolygonF hitbox, float rotationAngle,
                         const core::Damageable& damageableProperties):
        Object(id, position, std::move(hitbox), rotationAngle), Damageable(damageableProperties) {}

QString core::Building::getTypeName() {
    return typeName;
}

QString core::Building::typeName = "building";
