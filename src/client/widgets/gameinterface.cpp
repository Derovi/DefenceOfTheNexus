#include "gameinterface.h"
#include "gamemap.h"
#include "../screens/gamescreen.h"
#include "../../core/attributes/damageable.h"
#include "../app.h"
#include "../../core/attributes/damaging.h"
#include "../../core/attributes/mining.h"
#include "../../core/attributes/builder.h"
#include "../../core/attributes/moving.h"

#include <utility>

client::GameInterface::GameInterface(QPoint position, int height, int width,
                                     std::shared_ptr<core::GameWorld> gameWorld,
                                     int selectedUnitId):
        Widget(position), gameWorld(std::move(gameWorld)), selectedUnitId(selectedUnitId) {
    setHeight(height);
    setWidth(width);
    qDebug() << "interface constru";
    auto gameScreen = dynamic_cast<GameScreen*>(getParent());

    unitIcon = new UnitIcon(QPoint(642, 0), 342, 450);
    unitIcon->setBackground(QImage(":/interface/icon-background"));
    addChild(unitIcon);

    healthBar = new HealthBar(QPoint(1058, 0));
    healthBar->setBackground(QImage(":/interface/health-bar-background"));
    healthBar->setHealthLine(QImage(":/interface/health-bar-line"));
    addChild(healthBar);

    miniMap = new MiniMap(QPoint(700, 50), 350, 350);
    miniMap->setGameWorld(gameWorld);
    addChild(miniMap);


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
    speedIcon = QImage(":/interface/icon-speed");

    QFont font60 = App::getInstance()->getFont();
    font60.setPixelSize(60);
    damageView = new TextView(QPoint(1146, 138), "damage", font60);
    miningView = new TextView(QPoint(1146, 220), "mining", font60);
    armorView = new TextView(QPoint(1146, 302), "armor", font60);
    speedView = new TextView(QPoint(1146, 384), "speed", font60);

    addChild(damageView);
    addChild(miningView);
    addChild(armorView);
    addChild(speedView);

    aiButton = new ImageButton(QPoint(2040, 100), 66, 266);
    stopButton = new ImageButton(QPoint(2040, 188), 66, 266);
    killButton = new ImageButton(QPoint(2040, 276), 66, 266);

    aiButton->setImage(QImage(":/interface/button-ai"));
    stopButton->setImage(QImage(":/interface/button-stop"));
    killButton->setImage(QImage(":/interface/button-kill"));

    aiButton->setOnClick([&](QPoint point, bool leftButton) {
        GameMap* gameMap = dynamic_cast<GameScreen*>(getParent())->getGameMap();
        gameScreen->getMultiplayerInterface()->sendCommand(core::Command("ai",
                                                                         {QString::number(
                                                                                 selectedUnitId)}));
    });
    stopButton->setOnClick([&](QPoint point, bool leftButton) {
        GameMap* gameMap = dynamic_cast<GameScreen*>(getParent())->getGameMap();
        gameScreen->getMultiplayerInterface()->sendCommand(core::Command("stop",
                                                                         {QString::number(
                                                                                 selectedUnitId)}));
    });
    killButton->setOnClick([&](QPoint point, bool leftButton) {
        GameMap* gameMap = dynamic_cast<GameScreen*>(getParent())->getGameMap();
        gameScreen->getMultiplayerInterface()->sendCommand(core::Command("kill",
                                                                         {QString::number(
                                                                                 selectedUnitId)}));
    });

    addChild(aiButton);
    addChild(stopButton);
    addChild(killButton);

    qDebug() << "interface consru";
    QImage slotIcon = QImage(":/interface/icon-slot");
    for (int row = 0;
         row < 3;
         ++row) {
        for (int column = 0;
             column < 5;
             ++column) {
            buildSlots.push_back(new BuildSlot(QPoint(2784 + column * 168, row * 156),
                                               114, 114));
            buildSlots.back()->setImage(slotIcon);
            addChild(buildSlots.back());
        }
    }
}

int client::GameInterface::getSelectedUnitId() const {
    return selectedUnitId;
}

void client::GameInterface::setSelectedUnitId(int selectedUnitId) {
    GameInterface::selectedUnitId = selectedUnitId;
}

void client::GameInterface::paint(QPainter& painter) {
    GameScreen* gameScreen = dynamic_cast<GameScreen*>(getParent());
    GameMap* gameMap = gameScreen->getGameMap();

    // Resources
    painter.drawImage(QRect(0, 0, 114, 114), stoneIcon);
    painter.drawImage(QRect(0, 158, 114, 114), woodIcon);
    painter.drawImage(QRect(0, 316, 114, 114), ironIcon);

    int stone = 0;
    int wood = 0;
    int iron = 0;

    for (auto resource : gameWorld->getTeamResources(gameScreen->getTeam())) {
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

    std::shared_ptr<GraphicsObject> graphicsObject = nullptr;
    for (auto& object : gameMap->getGraphicsObjects()) {
        if (object->getObject()->getId() == selectedUnitId) {
            graphicsObject = object;
        }
    }


    //Attributes icons
    painter.drawImage(QRect(1058, 100, 60, 60), damageIcon);
    painter.drawImage(QRect(1058, 182, 60, 60), miningIcon);
    painter.drawImage(QRect(1058, 264, 60, 60), armorIcon);

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
            auto resource = std::dynamic_pointer_cast<core::Resource>(
                    graphicsObject->getObject()->getAttribute(core::Resource::attributeName));
            if (resource) {
                healthBar->setCurrentHp(resource->getAmount());
                healthBar->setMaxHp(200);
            } else {
                healthBar->setCurrentHp(0);
                healthBar->setMaxHp(0);
            }
        }
    } else {
        healthBar->setCurrentHp(0);
        healthBar->setMaxHp(0);
    }

    // Attributes
    painter.drawImage(QRect(1058, 100, 60, 60), damageIcon);
    painter.drawImage(QRect(1058, 182, 60, 60), miningIcon);
    painter.drawImage(QRect(1058, 264, 60, 60), armorIcon);
    painter.drawImage(QRect(1058, 346, 60, 60), speedIcon);

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
        for (int idx = 0;
             idx < buildSlots.size();
             ++idx) {
            if (idx < builder->getBuildList().size()) {
                QString slot = builder->getBuildList().value(idx);
                buildSlots[idx]->setObjectType(slot);
            } else {
                buildSlots[idx]->setObjectType("");
            }
        }
    }
    auto moving = std::dynamic_pointer_cast<core::Moving>(
            graphicsObject->getObject()->getAttribute(core::Moving::attributeName));
    if (moving) {
        speedView->setText(QString::number(static_cast<int>(moving->getMaxSpeed())));
    } else {
        speedView->setText(QString::number(0));
    }
}

void client::GameInterface::init() {
    GameScreen* gameScreen = dynamic_cast<GameScreen*>(getParent());
    GameMap* gameMap = gameScreen->getGameMap();
    core::GameWorld* world = gameMap->getGameWorld().get();
    setSelectedUnitId(-1);
    for (auto& object : gameWorld->getObjects()) {
        if (object->hasAttribute("moving") && object->getTeam() == gameScreen->getTeam()) {
            setSelectedUnitId(object->getId());
            gameMap->centerWindow(QPoint(object->getPosition().x(), object->getPosition().y()));
        }
    }
    if (getSelectedUnitId() == -1) {
        for (auto& object : gameWorld->getObjects()) {
            setSelectedUnitId(object->getId());
            gameMap->centerWindow(QPoint(object->getPosition().x(), object->getPosition().y()));
        }
    }
}
