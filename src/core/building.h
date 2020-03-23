#ifndef BUILDING_H
#define BUILDING_H

#include <QPointF>
#include <QPolygonF>

#include "damageable.h"
#include "object.h"

namespace core {

class Building : public Object, public Damageable {
  public:
    explicit Building(uint64_t id, QPointF position = QPointF(), QPolygonF hitbox = QPolygonF(),
             float rotationAngle = 0, const Damageable& damageableProperties = Damageable());
};

}  // namespace core

#endif // BUILDING_H
