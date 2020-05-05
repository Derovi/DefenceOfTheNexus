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
                                             QPoint(2000, 1000));

        engine->getGameWorld()->summonObject(
                utils::Factory::getObjectSignature("resourcebundle-stone").value(),
                QPoint(2200, 1000));

        engine->getGameWorld()->buildWall(QPoint(0, 1500), QPoint(2000, 500),
                                          utils::Factory::getObjectSignature("wall1").value(),
                                          utils::Factory::getObjectSignature("column1").value());
        engine->getGameWorld()->buildWall(QPoint(0, 1500), QPoint(-100, 50),
                                          utils::Factory::getObjectSignature("wall1").value(),
                                          utils::Factory::getObjectSignature("column1").value());
        engine->getGameWorld()->buildWall(QPoint(2000, 1500), QPoint(0, 500),
                                          utils::Factory::getObjectSignature("wall1").value(),
                                          utils::Factory::getObjectSignature("column1").value());
        engine->getGameWorld()->buildWall(QPoint(500, 1500), QPoint(0, 500),
                                          utils::Factory::getObjectSignature("wall1").value(),
                                          utils::Factory::getObjectSignature("column1").value());
        engine->getGameWorld()->buildWall(QPoint(200, 200), QPoint(800, 800),
                                          utils::Factory::getObjectSignature("wall1").value(),
                                          utils::Factory::getObjectSignature("column1").value());
        engine->getGameWorld()->buildWall(QPoint(-100, 500), QPoint(3, 9000),
                                          utils::Factory::getObjectSignature("wall1").value(),
                                          utils::Factory::getObjectSignature("column1").value());
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
