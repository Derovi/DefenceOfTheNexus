#include "strategy.h"

std::shared_ptr<core::Object> server::Strategy::getObject() const {
    return object;
}

server::Strategy::Strategy(std::shared_ptr<core::Object> object): object(object) {}

QStringList server::Strategy::getRequiredAttributes() {
    return QStringList();
}

QStringList server::Strategy::getStartAfter() {
    return QStringList();
}

void server::Strategy::cancelTargets() {}
