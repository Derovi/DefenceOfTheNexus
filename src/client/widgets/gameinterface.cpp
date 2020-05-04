#include "gameinterface.h"
#include "gamemap.h"
#include "../screens/gamescreen.h"
#include "../../core/attributes/damageable.h"
#include "../app.h"

#include <utility>

client::GameInterface::GameInterface(QPoint position,
                                     std::shared_ptr<core::GameWorld> gameWorld,
                                     int selectedUnitId):
        Widget(position), gameWorld(std::move(gameWorld)), selectedUnitId(selectedUnitId) {
    unitIcon = new UnitIcon(QPoint(642, 0), 342, 450);
    unitIcon->setBackground(QImage(":/interface/icon-background"));
    addChild(unitIcon);

    healthBar = new HealthBar(QPoint(1058, 0));
    healthBar->setBackground(QImage(":/interface/health-bar-background"));
    healthBar->setHealthLine(QImage(":/interface/health-bar-line"));
    addChild(healthBar);

    stoneIcon = QImage(":/interface/icon-stone");
    woodIcon = QImage(":/interface/icon-wood");
    ironIcon = QImage(":/interface/icon-iron");

    stoneView = new TextView(QPoint(140, 96), "stone", App::getInstance()->getFont());
    woodView = new TextView(QPoint(140, 254), "wood", App::getInstance()->getFont());
    ironView = new TextView(QPoint(140, 412), "iron", App::getInstance()->getFont());

    addChild(stoneView);
    addChild(woodView);
    addChild(ironView);
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

    // Resources
    painter.drawImage(QRect(0, 0, 114, 114), stoneIcon);
    painter.drawImage(QRect(0, 158, 114, 114), woodIcon);
    painter.drawImage(QRect(0, 316, 114, 114), ironIcon);

    int stone = 0;
    int wood = 0;
    int iron = 0;

    for (auto resource : gameWorld->getResources()) {
        if (resource.first == core::ResourceType::kStone) {
            stone = resource.second;
        }
        if (resource.first == core::ResourceType::kWood) {
            wood = resource.second;
        }
        if (resource.first == core::ResourceType::kIron) {
            iron = resource.second;
        }
    }

    stoneView->setText(QString::number(stone));
    woodView->setText(QString::number(wood));
    ironView->setText(QString::number(iron));
}
