#include <utility>

#include "building.h"

core::Building::Building(uint32_t id, QPointF position, QPolygonF hitbox, float rotationsAngle,
                         const core::Damageable& damageableProperties)
        : Object(id, position, std::move(hitbox), rotationsAngle), Damageable(damageableProperties) {}
