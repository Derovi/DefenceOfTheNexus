#include <utility>

#include "resource.h"
#include "resourcebundle.h"

core::ResourceBundle::ResourceBundle(uint64_t id, core::ResourceType resourceType, int maxHealth,
                                     QPointF position, QPolygonF hitbox, float rotationAngle):
        Object(id, position, std::move(hitbox), rotationAngle), Damageable(maxHealth, maxHealth),
        resourceType(resourceType) {}

core::ResourceType core::ResourceBundle::getResourceType() const {
    return resourceType;
}

void core::ResourceBundle::setType(const ResourceType& newType) {
    resourceType = newType;
}

QString core::ResourceBundle::getTypeName() {
    return "resourceBundle";
}
