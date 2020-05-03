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
    if (paused) {
        return;
    }
    Screen::draw();
}

client::GameMap* client::GameScreen::getGameMap() const {
    return gameMap;
}

client::GameScreen::GameScreen(const std::shared_ptr<core::GameWorld>& savedGameWorld):
        Screen(), paused(false) {
    gameMap = new GameMap();
    gameMap->setDisplayBounds(QRect(1920, 1080, 1920, 1080));
    Sprite background(QPixmap(":/sprites/background"), 1, 4, 4);
    background.setBackAndForthMode(true);
    gameMap->setBackground(background);
    addChild(gameMap);
    auto pauseButton = new ImageButton(QPoint(24, 24), 72, 72);
    pauseButton->setImage(QImage(":/images/cancel"));
    pauseButton->setOnClick([=](QPoint point) {
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
    }

    gameMap->setGameWorld(engine->getGameWorld());
    gameMap->setCommandQueue(engine->getCommandQueue());

    gameMap->setShowHitBoxes(true);
    engine->start();
}

const std::shared_ptr<server::Engine>& client::GameScreen::getEngine() const {
    return engine;
}

client::GameScreen::~GameScreen() {
    if (engine) {
        engine->finish();
    }
}
