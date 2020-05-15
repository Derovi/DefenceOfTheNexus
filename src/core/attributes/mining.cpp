#include "mining.h"

namespace core {

Mining::Mining():
        mining(false), miningSpeed(0), miningRadius(0), miningDelay(0), currentDelay(0) {}

Mining::Mining(int miningSpeed, int miningDelay, double miningRadius):
        mining(false), miningSpeed(miningSpeed), miningRadius(miningRadius),
        miningDelay(miningDelay),
        currentDelay(0) {}

int Mining::getMiningSpeed() const {
    return miningSpeed;
}

int Mining::getMiningDelay() const {
    return miningDelay;
}

int Mining::getCurrentDelay() const {
    return currentDelay;
}

double Mining::getMiningRadius() const {
    return miningRadius;
}

bool Mining::isMining() const {
    return mining;
}

void Mining::setMiningSpeed(int speed) {
    miningSpeed = speed;
}

void Mining::setMiningDelay(int delay) {
    miningDelay = delay;
}

void Mining::setCurrentDelay(int delay) {
    currentDelay = delay;
}

void Mining::setMiningRadius(double radius) {
    miningRadius = radius;
}

void Mining::setMining(bool mining) {
    this->mining = mining;
}

QString Mining::getAttributeName() {
    return attributeName;
}

std::shared_ptr<Attribute> Mining::clone() {
    return std::make_shared<Mining>(*this);
}

bool Mining::operator==(core::Mining mine) {
    return mining == mine.mining && miningDelay == mine.miningDelay &&
           miningRadius == mine.miningRadius && miningSpeed == mine.miningSpeed &&
           currentDelay == mine.currentDelay;
}

}  // namespace core
