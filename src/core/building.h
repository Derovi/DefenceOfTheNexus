#ifndef BUILDING_H
#define BUILDING_H

#include <QPointF>
#include <QString>
#include <QPolygonF>

#include "damageable.h"
#include "object.h"

namespace core {

// typeName = "building"
class Building : public Object, public Damageable {
  public:
    explicit Building(uint64_t id, QPointF position = QPointF(), QPolygonF hitbox = QPolygonF(),
                      float rotationAngle = 0, const Damageable& damageableProperties = Damageable());

    QString getTypeName() override;
};

}  // namespace core

#endif // BUILDING_H
