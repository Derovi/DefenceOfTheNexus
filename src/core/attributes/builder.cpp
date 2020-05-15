#include <memory>

#include <QString>

#include "builder.h"

QString core::Builder::getAttributeName() {
    return attributeName;
}

std::shared_ptr<core::Attribute> core::Builder::clone() {
    return std::make_shared<core::Builder>(*this);
}

const QStringList& core::Builder::getBuildList() const {
    return buildList;
}

void core::Builder::setBuildList(const QStringList& buildList) {
    Builder::buildList = buildList;
}

core::Builder::Builder() {}

core::Builder::Builder(const QStringList& buildList): buildList(buildList) {}

bool core::Builder::operator==(core::Builder object) {
    return object.buildList == buildList;
}
