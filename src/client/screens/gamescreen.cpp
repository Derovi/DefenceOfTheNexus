#include <QDebug>

#include "gamescreen.h"

#include "../app.h"
#include "../widgets/gamemap.h"
#include "../widgets/imagebutton.h"
#include "../../server/engine.h"
#include "../../core/attributes/moving.h"
#include "../../utils/factory.h"
#include "pausescreen.h"

void client::GameScreen::onPaused() {
    paused = true;
}

void client::GameScreen::onResumed() {
    paused = false;
    setLastPaintTime(QDateTime::currentDateTime());
}

void client::GameScreen::draw() {
    Screen::draw();
}

client::GameMap* client::GameScreen::getGameMap() const {
    return gameMap;
}

client::GameInterface* client::GameScreen::getInterface() const {
    return interface;
}

client::GameScreen::GameScreen(const std::shared_ptr<core::GameWorld>& savedGameWorld):
        Screen(), paused(false) {
    gameMap = new GameMap();
    gameMap->setDisplayBounds(QRect(1920, 1080, 1920, 1080));
    Sprite background(QPixmap(":/sprites/background"), 1, 1, 0);
//    background.setBackAndForthMode(true);
    gameMap->setBackground(background);
    addChild(gameMap);
    auto pauseButton = new ImageButton(QPoint(24, 24), 72, 72);
    pauseButton->setImage(QImage(":/images/cancel"));
    pauseButton->setOnClick([=](QPoint point, bool leftButton) {
        App::getInstance()->openScreen(std::make_shared<PauseScreen>());
    });

    addChild(pauseButton);

    GameConfiguration gameConfiguration;
    engine = std::make_shared<server::Engine>(gameConfiguration);

    if (savedGameWorld != nullptr) {
        engine->setGameWorld(savedGameWorld);
    } else {
        engine->getGameWorld()->summonObject(utils::Factory::getObjectSignature("test1").value(),
                                             QPoint(1800, 1200));

        engine->getGameWorld()->summonObject(
                utils::Factory::getObjectSignature("iron").value(),
                QPoint(842, 1422));

        engine->getGameWorld()->summonObject(
                utils::Factory::getObjectSignature("iron").value(),
                QPoint(3216, 566));


        engine->getGameWorld()->summonObject(
                utils::Factory::getObjectSignature("ore").value(),
                QPoint(272, 324));

        engine->getGameWorld()->summonObject(
                utils::Factory::getObjectSignature("ore").value(),
                QPoint(3036, 1912));


        engine->getGameWorld()->summonObject(
                utils::Factory::getObjectSignature("stone").value(),
                QPoint(3536, 1400));

        engine->getGameWorld()->summonObject(
                utils::Factory::getObjectSignature("cobblestone").value(),
                QPoint(3210, 270));

        engine->getGameWorld()->summonObject(
                utils::Factory::getObjectSignature("rock").value(),
                QPoint(932, 1960));

        engine->getGameWorld()->summonObject(
                utils::Factory::getObjectSignature("small-stone").value(),
                QPoint(1300, 622));

        engine->getGameWorld()->summonObject(
                utils::Factory::getObjectSignature("medium-stone").value(),
                QPoint(1600, 2004));

        engine->getGameWorld()->summonObject(
                utils::Factory::getObjectSignature("medium-stone").value(),
                QPoint(1850, 254));

        engine->getGameWorld()->summonObject(
                utils::Factory::getObjectSignature("big-stone").value(),
                QPoint(672, 468));

        engine->getGameWorld()->summonObject(
                utils::Factory::getObjectSignature("big-stone").value(),
                QPoint(340, 1570));


        engine->getGameWorld()->summonObject(
                utils::Factory::getObjectSignature("oak").value(),
                QPoint(1130, 218));

        engine->getGameWorld()->summonObject(
                utils::Factory::getObjectSignature("oak").value(),
                QPoint(180, 1982));

        engine->getGameWorld()->summonObject(
                utils::Factory::getObjectSignature("fir").value(),
                QPoint(444, 1052));

        engine->getGameWorld()->summonObject(
                utils::Factory::getObjectSignature("fir").value(),
                QPoint(3182, 1200));

        engine->getGameWorld()->summonObject(
                utils::Factory::getObjectSignature("conifer").value(),
                QPoint(2616, 262));

        engine->getGameWorld()->summonObject(
                utils::Factory::getObjectSignature("conifer").value(),
                QPoint(2188, 1984));

        engine->getGameWorld()->summonObject(
                utils::Factory::getObjectSignature("wite").value(),
                QPoint(1280, 960));

        engine->getGameWorld()->summonObject(
                utils::Factory::getObjectSignature("wite").value(),
                QPoint(3688, 2040));

        engine->getGameWorld()->summonObject(
                utils::Factory::getObjectSignature("nexus").value(),
                QPoint(1920, 1104));

        engine->getGameWorld()->summonObject(
                utils::Factory::getObjectSignature("gover").value(),
                QPoint(2278, 1060));

        engine->getGameWorld()->summonObject(
                utils::Factory::getObjectSignature("big-barrack").value(),
                QPoint(1800, 1420));

        engine->getGameWorld()->summonObject(
                utils::Factory::getObjectSignature("medium-barrack").value(),
                QPoint(1730, 806));

        engine->getGameWorld()->summonObject(
                utils::Factory::getObjectSignature("resource-bundle").value(),
                QPoint(450, 236));

        engine->getGameWorld()->summonObject(
                utils::Factory::getObjectSignature("dirt-rock").value(),
                QPoint(1283, 1800));

        engine->getGameWorld()->summonObject(
                utils::Factory::getObjectSignature("dirt-rock").value(),
                QPoint(3010, 1670));

        engine->getGameWorld()->summonObject(
                utils::Factory::getObjectSignature("grass").value(),
                QPoint(1118, 1226));

        engine->getGameWorld()->summonObject(
                utils::Factory::getObjectSignature("grass").value(),
                QPoint(2642, 1494));

        engine->getGameWorld()->summonObject(
                utils::Factory::getObjectSignature("grass").value(),
                QPoint(2478, 650));

        engine->getGameWorld()->summonObject(
                utils::Factory::getObjectSignature("grass").value(),
                QPoint(1650, 466));

        engine->getGameWorld()->summonObject(
                utils::Factory::getObjectSignature("big-tower").value(),
                QPoint(2010, 614));

        engine->getGameWorld()->summonObject(
                utils::Factory::getObjectSignature("medium-tower").value(),
                QPoint(2077, 1666), 180);

        engine->getGameWorld()->summonObject(
                utils::Factory::getObjectSignature("small-tower").value(),
                QPoint(198, 504), 45);

        engine->getGameWorld()->summonObject(
                utils::Factory::getObjectSignature("long-tower").value(),
                QPoint(1596, 1648));

        engine->getGameWorld()->summonObject(
                utils::Factory::getObjectSignature("special-tower").value(),
                QPoint(2540, 1640));

        engine->getGameWorld()->summonObject(
                utils::Factory::getObjectSignature("high-tower").value(),
                QPoint(1610, 592));

        engine->getGameWorld()->summonObject(utils::Factory::getObjectSignature("scorpion").value(),
                                             QPoint(200, 200));
        engine->getGameWorld()->buildWall(QPoint(500,0),QPoint(500,300), utils::Factory::getObjectSignature("wall1").value(),
                                          utils::Factory::getObjectSignature("column1").value());
        engine->getGameWorld()->summonObject(utils::Factory::getObjectSignature("mage").value(),
                                             QPoint(700, 200));
        engine->getGameWorld()->buildWall(QPoint(1000,0),QPoint(1000,300), utils::Factory::getObjectSignature("wall1").value(),
                                          utils::Factory::getObjectSignature("column1").value());
        engine->getGameWorld()->summonObject(utils::Factory::getObjectSignature("ogre").value(),
                                             QPoint(1200, 200));
        engine->getGameWorld()->buildWall(QPoint(1500,0),QPoint(1500,300), utils::Factory::getObjectSignature("wall1").value(),
                                          utils::Factory::getObjectSignature("column1").value());
        engine->getGameWorld()->summonObject(utils::Factory::getObjectSignature("scout").value(),
                                             QPoint(1700, 200));
        engine->getGameWorld()->buildWall(QPoint(2000,0),QPoint(2000,300), utils::Factory::getObjectSignature("wall1").value(),
                                          utils::Factory::getObjectSignature("column1").value());

        engine->getGameWorld()->buildWall(QPoint(0,0),QPoint(0,3000), utils::Factory::getObjectSignature("wall1").value(),
                                          utils::Factory::getObjectSignature("column1").value());

        engine->getGameWorld()->buildWall(QPoint(0,3000),QPoint(3000,3000), utils::Factory::getObjectSignature("wall1").value(),
                                          utils::Factory::getObjectSignature("column1").value());

        engine->getGameWorld()->buildWall(QPoint(3000,3000),QPoint(3000,0), utils::Factory::getObjectSignature("wall1").value(),
                                          utils::Factory::getObjectSignature("column1").value());

        engine->getGameWorld()->buildWall(QPoint(3000,0),QPoint(0,0), utils::Factory::getObjectSignature("wall1").value(),
                                          utils::Factory::getObjectSignature("column1").value());


        engine->getGameWorld()->summonObject(
                utils::Factory::getObjectSignature("resourcebundle-stone").value(),
                QPoint(2200, 1000));
        engine->getGameWorld()->summonObject(utils::Factory::getObjectSignature("scorpion").value(),
                                             QPoint(2200, 1200));
    }

    gameMap->setGameWorld(engine->getGameWorld());
    gameMap->setCommandQueue(engine->getCommandQueue());

    gameMap->setShowHitBoxes(true);
    engine->start();

    interface = new GameInterface(QPoint(152, 1710), 3536, 450, gameMap->getGameWorld());
    addChild(interface);
}

const std::shared_ptr<server::Engine>& client::GameScreen::getEngine() const {
    return engine;
}

client::GameScreen::~GameScreen() {
    if (engine) {
        engine->finish();
    }
}
