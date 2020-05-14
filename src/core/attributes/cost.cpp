#include "cost.h"

#include <utility>
#include "resource.h"

core::Cost::Cost(QVector<Resource> cost): cost(std::move(cost)) {}

core::Cost::Cost() {}

bool core::Cost::isEnough(const QPair<ResourceType, int>& playerResource) const {
    for (const Resource& resource : cost) {
        if (resource.getType() == playerResource.first) {
            return playerResource.second >= resource.getAmount();
        }
    }
    return true;
}

bool core::Cost::isEnough(const QVector<QPair<ResourceType, int>>& playerResources) const {
    for (const QPair<ResourceType, int>& playerResource : playerResources) {
        if (!isEnough(playerResource)) {
            return false;
        }
    }
    return true;
}

bool core::Cost::pay(QVector<QPair<ResourceType, int>>& playerResources) const {
    if (!isEnough(playerResources)) {
        return false;
    }
    for (QPair<ResourceType, int>& playerResource : playerResources) {
        for (const Resource& resource : cost) {
            if (playerResource.first == resource.getType()) {
                playerResource.second -= resource.getAmount();
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

bool core::Cost::operator==(const core::Cost& object) {
    if(cost.size()!=object.cost.size()){
        return false;
    }
    for(int j=0;j<cost.size();j++){
        if(!(cost[j]==object.cost[j])){
            return false;
        }
    }
    return true;
}
