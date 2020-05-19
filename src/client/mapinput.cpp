#include "../utils/factory.h"

#include "mapinput.h"
#include "../core/attributes/wall.h"
#include "screens/gamescreen.h"

client::MapInput::MapInput(client::GameMap* gameMap): gameMap(gameMap), objectType("") {}

void client::MapInput::abort() {
    points.clear();
    objectType.clear();
    qDebug() << "map input abort!";
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
    qDebug() << "map input objectType" << objectType;
    MapInput::objectType = objectType;
}

void client::MapInput::append(const QPoint& point) {
    qDebug() << "map input append!";
    points.push_back(point);
    auto objectSignature = utils::Factory::getObjectSignature(objectType);
    if (!objectSignature) {
        abort();
        return;
    }
    auto gameScreen = dynamic_cast<GameScreen*>(gameMap->getParent());
    if (objectSignature->hasAttribute(core::Wall::attributeName)) {
        if (points.size() == 0) {
            return;
        }
        qDebug() << "map input build wall!";
        gameScreen->getMultiplayerInterface()->sendCommand(core::Command("build_wall",
                                                       {
                                                               QString::number(gameScreen->getTeam()),
                                                               objectType,
                                                               QString::number(points.first().x()),
                                                               QString::number(points.first().y()),
                                                               QString::number(points[1].x()),
                                                               QString::number(points[1].y())}));
        abort();
    } else {
        qDebug() << "game map build!";
        gameScreen->getMultiplayerInterface()->sendCommand(core::Command("build",
                                                       {
                                                               QString::number(gameScreen->getTeam()),
                                                               objectType,
                                                               QString::number(points.first().x()),
                                                               QString::number(points.first().y())}));
        abort();
    }
}
