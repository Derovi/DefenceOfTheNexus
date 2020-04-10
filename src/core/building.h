#ifndef BUILDING_H
#define BUILDING_H

#include <QPointF>
#include <QString>
#include <QPolygonF>

#include "damageable.h"
#include "object.h"

namespace core {

// typeName = "building"
class Building : public Object {
  public:
    explicit Building(uint64_t id, QPointF position = QPointF(), QPolygonF hitbox = QPolygonF(),
                      float rotationAngle = 0, const Damageable& damageableProperties = Damageable());

    QString getTypeName() override;

    static QString typeName;

    Damageable& getDamageable();

    void setDamageable(const Damageable& damageable);

  private:
    Damageable damageable;
};

}  // namespace core

#endif // BUILDING_H
