#include "attackstrategy.h"

#include "../performers/damagingperformer.h"

namespace server {

AttackStrategy::AttackStrategy(std::shared_ptr<core::Object> object):
    Strategy(object), target(nullptr), damaging(nullptr) {}

void AttackStrategy::tick(std::shared_ptr<core::GameWorld> world, int timeDelta) {
    if (target == nullptr) {
        return;
    }
    damaging->setAttacking(true);
    if (!damaging_performer::isDamageable(getObject(), damaging, target)) {
        if (destPoint != nullptr) {
            *destPoint = target->getPosition();
        }
        return;
    } else {
        if (destPoint != nullptr) {
            *destPoint = getObject()->getPosition();
        }
        damaging_performer::damage(world, getObject(), damaging, target, timeDelta);
    }
}

QString AttackStrategy::getName() {
    return name;
}

QStringList AttackStrategy::getRequiredAttributes() {
    return requiredAttributes;
}

QStringList AttackStrategy::getStartAfter() {
    return startAfter;
}

void AttackStrategy::assign(DataBundle& dataBundle) {
    dataBundle.assign("destinationPoint", destPoint);
    dataBundle.assign("attackTarget", target);
    dataBundle.assign("damaging", damaging);
}

void AttackStrategy::cancelTargets() {
    target = nullptr;
    if (damaging != nullptr) {
        damaging->setAttacking(false);
    }
}

}  // namespace server
