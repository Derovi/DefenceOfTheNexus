#include "damagingperformer.h"

#include <cmath>

#include <QLineF>
#include <QDebug>

#include "../../core/attributes/damageable.h"
#include "../../core/attributes/moving.h"
#include "../../core/attributes/bullet.h"
#include "../../utils/factory.h"
#include "damageableperformer.h"

namespace server::damaging_performer {

bool isDamageable(std::shared_ptr<core::Object> object, std::shared_ptr<core::Damaging> damaging,
                  std::shared_ptr<core::Object> target) {
//    float angle = object->getSightAngle();
//    double length = damaging->getAttackRadius();
//    QPointF attackDirection(length * std::cos(angle), length * std::sin(angle));
//    QPolygonF attackLine;
//    attackLine.append(object->getPosition());
//    attackLine.append(object->getPosition() + attackDirection);
//    return attackLine.intersects(target->getHitboxOnMap());
    return QLineF(target->getPosition(), object->getPosition()).length() < damaging->getAttackRadius();
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
            auto bulletType = damaging->getBulletType();
            if (bulletType.isEmpty()) {
                world->generateEvent(
                        core::Event(core::Event::Type::HIT_EVENT,
                                    {QString::number(object->getId())}));
                damageable_performer::inflictDamage(world, target, damageable,
                                                    damaging->getDamage());
            } else {
                auto bullet = world->summonObject(
                        utils::Factory::getObjectSignature(bulletType).value(),
                        object->getPosition().toPoint());

                auto moving = std::dynamic_pointer_cast<core::Moving>(
                        bullet->getAttribute("moving"));
                auto direction = QVector2D(target->getPosition() - object->getPosition());
                moving->setDirection(direction);
                bullet->setRotationAngle(std::atan2(direction.y(), direction.x()));

                auto bulletAttr = std::dynamic_pointer_cast<core::Bullet>(
                        bullet->getAttribute("bullet"));
                bulletAttr->setOwner(object);
                bulletAttr->setDamage(damaging->getDamage());
                bulletAttr->setRange(damaging->getAttackRadius());

                qDebug() << "Created bullet successfully" << endl;
            }
        } else {
            damaging->setAttacking(false);
        }
    }
}

}  // namespace server::damaging_performer
