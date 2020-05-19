#include "towerstrategy.h"

#include <cmath>

#include <QLineF>

#include "../performers/damagingperformer.h"

namespace server {

TowerStrategy::TowerStrategy(std::shared_ptr<core::Object> object):
    Strategy(object), target(nullptr), damaging(nullptr), targetId(-1) {}

QString TowerStrategy::getName() {
    return name;
}

void TowerStrategy::assign(DataBundle& dataBundle) {
    dataBundle.assign("damaging", damaging);
}

void TowerStrategy::tick(std::shared_ptr<core::GameWorld> world, int timeDelta) {
    if (targetId == -1 || !world->getObjects().contains(targetId)) {
        chooseTarget(world);
    } else {
        double distance = QLineF(target->getPosition(), getObject()->getPosition()).length();
        if (distance > damaging->getAttackRadius()) {
            chooseTarget(world);
        }
    }
    if (targetId == -1) {
        return;
    }
    auto direction = target->getPosition() - getObject()->getPosition();
    getObject()->setRotationAngle(std::atan2(direction.y(), direction.x()));
    getObject()->setSightAngle(std::atan2(direction.y(), direction.x()));
    damaging_performer::damage(world, getObject(), damaging, target, timeDelta);
}

void TowerStrategy::chooseTarget(std::shared_ptr<core::GameWorld> world) {
    const auto& self = getObject();
    for (const auto& object : world->getObjects()) {
        if (!world->areEnemies(object->getTeam(), self->getTeam())) {
            continue;
        }
        double distance = QLineF(object->getPosition(), self->getPosition()).length();
        if (distance > damaging->getAttackRadius() || !object->hasAttribute("damageable")) {
            continue;
        }
        target = object;
        targetId = object->getId();
        return;
    }
    targetId = -1;
    target = nullptr;
}

void TowerStrategy::cancelTargets() {
    target = nullptr;
    targetId = -1;
}

}  // namespace server
