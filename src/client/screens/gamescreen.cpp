#include <QDebug>

#include "gamescreen.h"

#include "../mainwindow.h"
#include "../widgets/gamemap.h"
#include "../widgets/imagebutton.h"
#include "../../server/engine.h"
#include "../../core/attributes/moving.h"
#include "../../utils/factory.h"

void client::GameScreen::onPaused() {

}

void client::GameScreen::onResumed() {

}

client::GameScreen::GameScreen() : Screen() {
    auto gameMap = new GameMap();
    gameMap->setDisplayBounds(QRect(1920, 1080, 1920, 1080));
    Sprite background(QPixmap(":/sprites/background"), 1, 4, 4);
    background.setBackAndForthMode(true);
    gameMap->setBackground(background);
    addChild(gameMap);
    auto closeButton = new ImageButton(QPoint(24, 24), 72, 72);
    closeButton->setImage(QImage(":/images/cancel"));
    closeButton->setOnClick([=](QPoint point) {
        QThread* thread = QThread::create([&] {
            QThread::msleep(1);
            MainWindow::getInstance()->closeScreen();
        });
        thread->start();
    });

    addChild(closeButton);

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
