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

const QString core::Resource::attributeName = "resource";

std::shared_ptr<core::Attribute> core::Resource::clone() {
    return std::shared_ptr<Attribute>(new Resource(*this));
}
