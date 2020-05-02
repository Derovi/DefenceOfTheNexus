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

}

void client::GameScreen::onResumed() {

}

client::GameMap* client::GameScreen::getGameMap() const {
    return gameMap;
}

client::GameScreen::GameScreen() : Screen() {
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
    engine = std::shared_ptr<server::Engine>(new server::Engine(gameConfiguration));

    gameMap->setGameWorld(engine->getGameWorld());
    gameMap->setCommandQueue(engine->getCommandQueue());

    gameMap->getGameWorld()->summonObject(utils::Factory::getObjectSignature("test1").value(),
                                          QPoint(2000, 1000));

    gameMap->getGameWorld()->summonObject(utils::Factory::getObjectSignature("test2").value(),
                                          QPoint(3000, 2000));

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
