#include "cost.h"

core::Cost::Cost(QMap<std::shared_ptr<core::Object>, core::ResCost>& hashMap) {
    cost = hashMap;
}

QMap<std::shared_ptr<core::Object>, core::ResCost>& core::Cost::getCost() {
    return cost;
}

void core::Cost::setCost(QMap<std::shared_ptr<core::Object>, core::ResCost> newCost) {
    cost = newCost;
}

QString core::Cost::getAttributeName() {
    return attributeName;
}

QString core::Cost::attributeName = "cost";

std::shared_ptr<core::Attribute> core::Cost::clone() {
    return std::make_shared<core::Cost>(*this);

}
