#ifndef BUILDING_H
#define BUILDING_H


#include <QPointF>
#include <QPolygonF>

#include "damageable.h"
#include "object.h"

namespace core {

class Building : public Object, public Damageable {
  public:
    Building() = delete;

    Building(uint32_t id, QPointF position = QPointF(), QPolygonF hitbox = QPolygonF(), float rotationsAngle = 0,
             const Damageable& damageableProperties = Damageable());

    ~Building() override = default;
};

}  // namespace core


#endif // BUILDING_H
