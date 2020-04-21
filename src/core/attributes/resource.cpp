#include "resource.h"

#include <cmath>
#include <random>

core::Resource::Resource(core::ResourceType type, int amount, double miningSpeedModifier):
        type(type), amount(amount), miningSpeedModifier(1) {}

core::ResourceType core::Resource::getType() const {
    return type;
}

int core::Resource::getAmount() const {
    return amount;
}

void core::Resource::setAmount(int newAmount) {
    amount = newAmount;
}

double core::Resource::getMiningSpeedModifier() const {
    return miningSpeedModifier;
}

void core::Resource::setMiningSpeedModifier(double modifier) {
    miningSpeedModifier = modifier;
}

int core::Resource::mine(int speed) {
    int guaranteed = static_cast<int>(miningSpeedModifier);
    if (std::abs(miningSpeedModifier - guaranteed) < 0.1) {
        int mined = std::min(speed * guaranteed, amount);
        amount -= mined;
        return mined;
    }

    //! Randomly picks either 0 or 1 with given probability (%)
    static const auto random = [](int probability) -> int {
        std::mt19937 rnd(42);
        std::uniform_int_distribution<> uPercents(0, 99);
        return uPercents(rnd) < probability;
    };

    int mined = std::min(speed * guaranteed
            + random(static_cast<int>((miningSpeedModifier - guaranteed) * 100)), amount);
    amount -= mined;
    return mined;
}

void core::Resource::setType(ResourceType newType) {
    type = newType;
}

QString core::Resource::getAttributeName() {
    return attributeName;
}

const QString core::Resource::attributeName = "resource";

std::shared_ptr<core::Attribute> core::Resource::clone() {
    return std::make_shared<Resource>(*this);
}
