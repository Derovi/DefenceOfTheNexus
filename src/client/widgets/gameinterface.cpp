#include "gameinterface.h"
#include "gamemap.h"
#include "../screens/gamescreen.h"
#include "../../core/attributes/damageable.h"
#include "../app.h"
#include "../../core/attributes/damaging.h"
#include "../../core/attributes/mining.h"
#include "../../core/attributes/builder.h"

#include <utility>

client::GameInterface::GameInterface(QPoint position, int height, int width,
                                     std::shared_ptr<core::GameWorld> gameWorld,
                                     int selectedUnitId):
        Widget(position), gameWorld(std::move(gameWorld)), selectedUnitId(selectedUnitId) {
    setHeight(height);
    setWidth(width);

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

    damageIcon = QImage(":/interface/icon-damage");
    miningIcon = QImage(":/interface/icon-mining");
    armorIcon = QImage(":/interface/icon-armor");

    QFont font60 = App::getInstance()->getFont();
    font60.setPixelSize(60);
    damageView = new TextView(QPoint(1146, 138), "damage", font60);
    miningView = new TextView(QPoint(1146, 220), "mining", font60);
    armorView = new TextView(QPoint(1146, 302), "armor", font60);

    addChild(damageView);
    addChild(miningView);
    addChild(armorView);

    aiButton = new ImageButton(QPoint(2040, 100), 66, 266);
    stopButton = new ImageButton(QPoint(2040, 188), 66, 266);
    killButton = new ImageButton(QPoint(2040, 276), 66, 266);

    aiButton->setImage(QImage(":/interface/button-ai"));
    stopButton->setImage(QImage(":/interface/button-stop"));
    killButton->setImage(QImage(":/interface/button-kill"));

    aiButton->setOnClick([&](QPoint point, bool leftButton) {
        GameMap* gameMap = dynamic_cast<GameScreen*>(getParent())->getGameMap();
        gameMap->getCommandQueue()->push(core::Command("ai",
                                                       {QString::number(selectedUnitId)}));
    });
    stopButton->setOnClick([&](QPoint point, bool leftButton) {
        GameMap* gameMap = dynamic_cast<GameScreen*>(getParent())->getGameMap();
        gameMap->getCommandQueue()->push(core::Command("stop",
                                                       {QString::number(selectedUnitId)}));
    });
    killButton->setOnClick([&](QPoint point, bool leftButton) {
        GameMap* gameMap = dynamic_cast<GameScreen*>(getParent())->getGameMap();
        gameMap->getCommandQueue()->push(core::Command("kill",
                                                       {QString::number(selectedUnitId)}));
    });

    addChild(aiButton);
    addChild(stopButton);
    addChild(killButton);

    slotIcon = QImage(":/interface/icon-slot");
}

int client::GameInterface::getSelectedUnitId() const {
    return selectedUnitId;
}

void client::GameInterface::setSelectedUnitId(int selectedUnitId) {
    GameInterface::selectedUnitId = selectedUnitId;
}

void client::GameInterface::paint(QPainter& painter) {
    GameMap* gameMap = dynamic_cast<GameScreen*>(getParent())->getGameMap();
    std::shared_ptr<GraphicsObject> graphicsObject = nullptr;
    for (auto& object : gameMap->getGraphicsObjects()) {
        if (object->getObject()->getId() == selectedUnitId) {
            graphicsObject = object;
        }
    }

    if (!graphicsObject) {
        return;
    }

    auto object = graphicsObject->getObject();

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

    // Attributes
    painter.drawImage(QRect(1058, 100, 60, 60), damageIcon);
    painter.drawImage(QRect(1058, 182, 60, 60), miningIcon);
    painter.drawImage(QRect(1058, 264, 60, 60), armorIcon);

    auto damaging = std::dynamic_pointer_cast<core::Damaging>(
            graphicsObject->getObject()->getAttribute(core::Damaging::attributeName));
    damageView->setText(QString::number(damaging ? damaging->getDamage() : 0));

    auto mining = std::dynamic_pointer_cast<core::Mining>(
            graphicsObject->getObject()->getAttribute(core::Mining::attributeName));
    miningView->setText(QString::number(mining ? mining->getMiningSpeed() : 0));

    //!TODO armor display
    auto armor = nullptr;
    armorView->setText(QString::number(0) + "%");

    // Build slots
    auto builder = std::dynamic_pointer_cast<core::Builder>(
            object->getAttribute(core::Builder::attributeName));
    if (builder) {
        for (int idx = 0; idx < 15 && idx < builder->getBuildList().size(); ++idx) {
            QString slot = builder->getBuildList().value(idx);
            painter.drawImage(QRect(2784, 0, 114, 114), slotIcon);
        }
    }
}
