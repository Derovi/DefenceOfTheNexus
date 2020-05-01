#include "minestrategy.h"

#include "../performers/miningperformer.h"

server::MineStrategy::MineStrategy(std::shared_ptr<core::Object> object):
    Strategy(object), mining(nullptr), miningTarget(nullptr) {}

void server::MineStrategy::tick(std::shared_ptr<core::GameWorld> world, int timeDelta) {
    if (miningTarget != nullptr) {
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
    dataBundle.assign("mining", mining);
    dataBundle.assign("miningTarget", miningTarget);
}

void server::MineStrategy::cancelTargets() {
    miningTarget = nullptr;
}
