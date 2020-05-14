#include "wall.h"

core::Wall::Wall(core::WallType type) {
    Wall::type = type;
}

core::WallType core::Wall::getType() const {
    return type;
}

void core::Wall::setType(core::WallType newType) {
    type = newType;
}

QString core::Wall::getAttributeName() {
    return attributeName;
}

QString core::Wall::attributeName = "wall";

std::shared_ptr<core::Attribute> core::Wall::clone() {
    return std::make_shared<core::Wall>(*this);
}

bool core::Wall::operator==(core::Wall wall) {
    return getType() == wall.getType();
}
