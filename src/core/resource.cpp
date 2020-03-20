#include "resource.h"

core::Resource::Resource(core::ResourceType type, int amount) : type(type), amount(amount) {}

core::ResourceType core::Resource::getType() const {
    return type;
}

int core::Resource::getAmount() const {
    return amount;
}

void core::Resource::setAmount(int newAmount) {
    amount = newAmount;
}
