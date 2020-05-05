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
        if (points.size() == 0) {
            return;
        }
        gameMap->getCommandQueue()->push(core::Command("build_wall",
                                                       {
                                                               objectType,
                                                               QString::number(points.first().x()),
                                                               QString::number(points.first().y()),
                                                               QString::number(points[1].x()),
                                                               QString::number(points[1].y())}));
        abort();
    } else {
        gameMap->getCommandQueue()->push(core::Command("build",
                                                       {
                                                               objectType,
                                                               QString::number(points.first().x()),
                                                               QString::number(
                                                                       points.first().y())}));
        abort();
    }
}
