#include "../utils/factory.h"

#include "mapinput.h"
#include "../core/attributes/wall.h"

client::MapInput::MapInput(client::GameMap* gameMap): gameMap(gameMap) {}

void client::MapInput::abort() {
    points.clear();
    objectType.clear();
}

bool client::MapInput::isWaiting() {
    return !objectType.isEmpty();
}

const QString& client::MapInput::getObjectType() const {
    return objectType;
}

const QVector<QPoint>& client::MapInput::getPoints() const {
    return points;
}

client::GameMap* client::MapInput::getGameMap() const {
    return gameMap;
}

void client::MapInput::setObjectType(const QString& objectType) {
    MapInput::objectType = objectType;
}

void client::MapInput::append(const QPoint& point) {
    points.push_back(point);
    auto objectSignature = utils::Factory::getObjectSignature(objectType);
    if (!objectSignature) {
        abort();
        return;
    }
    if (objectSignature->hasAttribute(core::Wall::attributeName)) {

    } else {

    }
}
