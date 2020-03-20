#include <utility>

#include "unit.h"

core::Unit::Unit(uint32_t id, QPointF position, QPolygonF hitbox, float rotationAngle,
                 const core::Moving& movingProperties, const core::Damaging& damagingProperties,
                 const core::Damageable& damageableProperties)
        : Object(id, position, std::move(hitbox), rotationAngle),
          Moving(movingProperties),
          Damaging(damagingProperties),
          Damageable(damageableProperties) {}
