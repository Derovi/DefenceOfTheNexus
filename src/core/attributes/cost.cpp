#include "cost.h"

#include <utility>
#include "resource.h"

core::Cost::Cost(QVector<Resource> cost): cost(std::move(cost)) {}

core::Cost::Cost() {}

bool core::Cost::isEnough(const core::Resource& playerResource) const {
    for (const Resource& resource : cost) {
        if (resource.getType() == playerResource.getType()) {
            return playerResource.getAmount() >= resource.getAmount();
        }
    }
    return true;
}

bool core::Cost::isEnough(const QVector<Resource>& playerResources) const {
    for (const Resource& playerResource : playerResources) {
        if (!isEnough(playerResource)) {
            return false;
        }
    }
    return true;
}

bool core::Cost::pay(QVector<Resource>& playerResources) const {
    if (!isEnough(playerResources)) {
        return false;
    }
    for (Resource& playerResource : playerResources) {
        for (const Resource& resource : cost) {
            if (playerResource.getType() == resource.getType()) {
                playerResource.setAmount(playerResource.getAmount() - resource.getAmount());
                break;
            }
        }
    }
    return true;
}

const QVector<core::Resource>& core::Cost::getCost() const {
    return cost;
}

QString core::Cost::getAttributeName() {
    return attributeName;
}

QString core::Cost::attributeName = "cost";

std::shared_ptr<core::Attribute> core::Cost::clone() {
    return std::make_shared<core::Cost>(*this);

}
