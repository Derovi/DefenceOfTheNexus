#include "minestrategy.h"

#include "../performers/miningperformer.h"

server::MineStrategy::MineStrategy(std::shared_ptr<core::Object> object): Strategy(object) {}

void server::MineStrategy::tick(std::shared_ptr<core::GameWorld> world, int timeDelta) {
    mining_performer::mine(world, getObject(), mining, timeDelta);
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
}
