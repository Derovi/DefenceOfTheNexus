#include "damagingperformer.h"

#include <cmath>

#include <QLineF>
#include <QDebug>

#include "../../core/attributes/damageable.h"
#include "damageableperformer.h"

namespace server::damaging_performer {

bool isDamageable(std::shared_ptr<core::Object> object, std::shared_ptr<core::Damaging> damaging,
                  std::shared_ptr<core::Object> target) {
    float angle = object->getRotationAngle();
    double length = damaging->getAttackRadius();
    QPointF attackDirection(length * std::cos(angle), length * std::sin(angle));
    QPolygonF attackLine;
    attackLine.append(object->getPosition());
    attackLine.append(object->getPosition() + attackDirection);
    return attackLine.intersects(target->getHitboxOnMap());
}

void damage(std::shared_ptr<core::GameWorld> world, std::shared_ptr<core::Object> object,
            std::shared_ptr<core::Damaging> damaging, std::shared_ptr<core::Object> target,
            int timeDelta) {
    int delayLeft = damaging->getCurrentDelay() - timeDelta;
    if (delayLeft > 0) {
        damaging->setCurrentDelay(delayLeft);
        return;
    }
    damaging->setCurrentDelay(damaging->getAttackDelay());

    if (isDamageable(object, damaging, target)) {
        std::shared_ptr<core::Damageable> damageable = std::dynamic_pointer_cast<core::Damageable>(
                target->getAttribute("damageable"));
        if (damageable != nullptr && damageable->getHealth() > 0) {
            world->generateEvent(
                    core::Event(core::Event::Type::HIT_EVENT, {QString::number(object->getId())}));
            damageable_performer::inflictDamage(world, target, damageable, damaging->getDamage());
        } else {
            damaging->setAttacking(false);
        }
    }
}

}  // namespace server::damaging_performer
