#ifndef RESOURCEBUNDLE_H
#define RESOURCEBUNDLE_H

#include <QPointF>
#include <QPolygonF>

#include "damageable.h"
#include "object.h"
#include "resource.h"

namespace core {

class ResourceBundle : public Object, public Damageable {
  public:
    ResourceBundle(uint64_t id, ResourceType resourceType, int maxHealth, QPointF position = QPointF(),
                   QPolygonF hitbox = QPolygonF(), float rotationAngle = 0);

    ResourceType getResourceType() const;

  private:
    ResourceType resourceType;
};

}  // namespace core


#endif // RESOURCEBUNDLE_H
