#ifndef UNIT_H
#define UNIT_H

#include <QPointF>
#include <QPolygonF>

#include "damageable.h"
#include "damaging.h"
#include "moving.h"
#include "object.h"

namespace core {

// typeName = "unit";
class Unit : public Object, public Moving, public Damaging, public Damageable {
  public:
    explicit Unit(uint64_t id, QPointF position = QPointF(), QPolygonF hitbox = QPolygonF(),
                  float rotationAngle = 0,
                  const Moving& movingProperties = Moving(),
                  const Damaging& damagingProperties = Damaging(),
                  const Damageable& damageableProperties = Damageable());

    QString getTypeName() override;

    static QString typeName;
};

}  // namespace core

#endif // UNIT_H
