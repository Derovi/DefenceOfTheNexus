#include "minestrategy.h"

#include "../performers/miningperformer.h"

server::MineStrategy::MineStrategy(std::shared_ptr<core::Object> object):
    Strategy(object), mining(nullptr), miningTarget(nullptr) {}

void server::MineStrategy::tick(std::shared_ptr<core::GameWorld> world, int timeDelta) {
    if (miningTarget == nullptr) {
        return;
    }
    if (!mining_performer::isMineable(getObject(), mining, miningTarget)) {
        if (destPoint != nullptr) {
            *destPoint = miningTarget->getPosition();
        }
        mining->setMining(false);
    } else {
        if (destPoint != nullptr) {
            *destPoint = getObject()->getPosition();
        }
        mining->setMining(true);
        mining_performer::mine(world, getObject(), mining, miningTarget, timeDelta);
    }
}

QString server::MineStrategy::getName() {
    return name;
}

QStringList server::MineStrategy::getRequiredAttributes() {
    return requiredAttributes;
}

QStringList server::MineStrategy::getStartAfter() {
    return startAfter;
}

void server::MineStrategy::assign(server::DataBundle& dataBundle) {
    dataBundle.assign("destinationPoint", destPoint);
    dataBundle.assign("mining", mining);
    dataBundle.assign("miningTarget", miningTarget);
}

void server::MineStrategy::cancelTargets() {
    miningTarget = nullptr;
    if (mining != nullptr) {
        mining->setMining(false);
    }
}
