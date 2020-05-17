#include "bulletstrategy.h"

#include <QLineF>

#include "../../core/attributes/damaging.h"
#include "../performers/movingperformer.h"
#include "../performers/damageableperformer.h"

namespace server {

BulletStrategy::BulletStrategy(std::shared_ptr<core::Object> object):
    Strategy(object) {}

void BulletStrategy::tick(std::shared_ptr<core::GameWorld> world, int timeDelta) {
    std::shared_ptr<core::Object> hitObject = nullptr;

    uint64_t bulletId = getObject()->getId();
    QPointF bulletPos = getObject()->getPosition();
    for (const auto& object : world->getObjects()) {
        if (object->getId() != bulletId
            && object->getHitboxOnMap().containsPoint(bulletPos, Qt::OddEvenFill)) {
            hitObject = object;
            break;
        }
    }

    if (hitObject != nullptr && hitObject->getId() != bullet->getOwnerId()) {
        auto damageable = std::dynamic_pointer_cast<core::Damageable>(
            hitObject->getAttribute("damageable"));
        if (damageable != nullptr) {
            damageable_performer::inflictDamage(world, hitObject, damageable, bullet->getDamage());
        }
        world->getObjects().remove(getObject()->getId());
    } else {
        double travelled = QLineF(getObject()->getPosition(), bullet->getShooterPos()).length();
        if (travelled > bullet->getRange()) {
            world->getObjects().remove(getObject()->getId());
        }
        moving_performer::move(getObject(), timeDelta, *moving);
    }
}

QString BulletStrategy::getName() {
    return name;
}

QStringList BulletStrategy::getRequiredAttributes() {
    return requiredAttributes;
}

QStringList BulletStrategy::getStartAfter() {
    return startAfter;
}

void BulletStrategy::assign(DataBundle& dataBundle) {
    dataBundle.assign("bullet", bullet);
    dataBundle.assign("moving", moving);
}

void BulletStrategy::cancelTargets() {
    throw std::logic_error("bullet is unstoppable :|");
}

}  // namespace server

