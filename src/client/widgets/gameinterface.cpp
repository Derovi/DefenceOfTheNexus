#include "gameinterface.h"
#include "gamemap.h"
#include "../screens/gamescreen.h"

#include <utility>

client::GameInterface::GameInterface(QPoint position,
                                     std::shared_ptr<core::GameWorld> gameWorld,
                                     int selectedUnitId):
        Widget(position), gameWorld(std::move(gameWorld)), selectedUnitId(selectedUnitId) {
    unitIcon = new UnitIcon(QPoint(1000, 0), 500, 500);

    addChild(unitIcon);
}

void client::GameInterface::paint(QPainter& painter) {
    GameMap* gameMap = dynamic_cast<GameScreen*>(getParent())->getGameMap();
    std::shared_ptr<GraphicsObject> graphicsObject = nullptr;
    for (auto& object : gameMap->getGraphicsObjects()) {
        if (object->getObject()->getId() == selectedUnitId) {
            graphicsObject = object;
        }
    }
    unitIcon->setGraphicsObject(graphicsObject);
}
