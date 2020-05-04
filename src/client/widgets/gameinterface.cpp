#include "gameinterface.h"
#include "gamemap.h"
#include "../screens/gamescreen.h"
#include "../../core/attributes/damageable.h"

#include <utility>

client::GameInterface::GameInterface(QPoint position,
                                     std::shared_ptr<core::GameWorld> gameWorld,
                                     int selectedUnitId):
        Widget(position), gameWorld(std::move(gameWorld)), selectedUnitId(selectedUnitId) {
    unitIcon = new UnitIcon(QPoint(642, 0), 342, 450);
    addChild(unitIcon);

    healthBar = new HealthBar(QPoint(1058, 0));
    addChild(healthBar);
}

void client::GameInterface::paint(QPainter& painter) {
    GameMap* gameMap = dynamic_cast<GameScreen*>(getParent())->getGameMap();
    std::shared_ptr<GraphicsObject> graphicsObject = nullptr;
    for (auto& object : gameMap->getGraphicsObjects()) {
        if (object->getObject()->getId() == selectedUnitId) {
            graphicsObject = object;
        }
    }

    // Unit icon
    unitIcon->setGraphicsObject(graphicsObject);

    // Health bar
    if (graphicsObject) {
        auto damageable = std::dynamic_pointer_cast<core::Damageable>(
                graphicsObject->getObject()->getAttribute(core::Damageable::attributeName));
        if (damageable) {
            healthBar->setCurrentHp(damageable->getHealth());
            healthBar->setMaxHp(damageable->getMaxHealth());
        } else {
            healthBar->setCurrentHp(0);
            healthBar->setMaxHp(0);
        }
    } else {
        healthBar->setCurrentHp(0);
        healthBar->setMaxHp(0);
    }
}
