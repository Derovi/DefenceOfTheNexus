#include "resource.h"

core::Resource::Resource(core::ResourceType type, int amount): type(type), amount(amount) {}

core::ResourceType core::Resource::getType() const {
    return type;
}

int core::Resource::getAmount() const {
    return amount;
}

void core::Resource::setAmount(int newAmount) {
    amount = newAmount;
}

void core::Resource::setType(ResourceType newType) {
    type = newType;
}

QString core::Resource::getAttributeName() {
    return attributeName;
}

std::shared_ptr<core::Attribute> core::Resource::clone() {
    return std::make_shared<core::Resource>(*this);
}
