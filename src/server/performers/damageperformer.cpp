#include "damagingperformer.h"

#include <cmath>

#include <QVector2D>
#include <QLineF>

#include "../../core/damageable.h"
#include "damageableperformer.h"

namespace server::damaging_performer {

void damage(std::shared_ptr<core::GameWorld> world, std::shared_ptr<core::Object> object,
            double timeDelta, std::shared_ptr<core::Damaging> damaging) {
    double delayLeft = damaging->getCurrentDelay() - timeDelta;
    if (delayLeft > 0) {
        damaging->setCurrentDelay(delayLeft);
        return;
    }
    damaging->setCurrentDelay(damaging->getAttackDelay());

    float angle = object->getRotationAngle();
    double length = damaging->getAttackRadius();
    QPointF attackDirection(length * std::cos(angle), length * std::sin(angle));
    QPolygonF attackLine;
    attackLine.append(object->getPosition());
    attackLine.append(object->getPosition() + attackDirection);
    for (auto target : world->getObjects()) {
        if (target == object || !attackLine.intersects(target->getHitbox())) {
            continue;
        }
        std::shared_ptr<core::Damageable> damageable = std::dynamic_pointer_cast<core::Damageable>(
                target->getAttribute("damageable"));
        if (damageable != nullptr) {
            damageable_performer::inflictDamage(world, target, damaging->getDamage(), damageable);
        }
    }
}

}  // namespace server::damaging_performer
