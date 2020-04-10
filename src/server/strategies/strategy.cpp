#include "strategy.h"

core::Object* server::Strategy::getObject() const {
    return object;
}

server::Strategy::Strategy(core::Object* object) : object(object) {}

QStringList server::Strategy::getRequiredAttributes() {
    return QStringList();
}

QStringList server::Strategy::getStartAfter() {
    return QStringList();
}

server::Strategy::~Strategy() = default;
