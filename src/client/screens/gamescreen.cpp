#include <QDebug>

#include "../mainwindow.h"
#include "../widgets/gamemap.h"
#include "../widgets/imagebutton.h"
#include "../../server/engine.h"
#include "../../core/attributes/moving.h"

#include "gamescreen.h"

void client::GameScreen::onPaused() {

}

void client::GameScreen::onResumed() {

}

client::GameScreen::GameScreen() {
    GameMap* gameMap = new GameMap();
    gameMap->setDisplayBounds(QRect(1920,1080,1920,1080));
    Sprite background(QPixmap(":/sprites/background"), 1, 4, 4);
    background.setBackAndForthMode(true);
    gameMap->setBackground(background);
    addChild(gameMap);
    ImageButton* closeButton = new ImageButton(QPoint(24, 24), 72, 72);
    closeButton->setImage(QImage(":/images/cancel"));
    closeButton->setOnClick([=](QPoint point) {
        MainWindow::getInstance()->closeScreen();
    });

    addChild(closeButton);

    GameConfiguration gameConfiguration;
    engine = std::shared_ptr<server::Engine>(new server::Engine(gameConfiguration));
    std::shared_ptr<core::Object> object = std::shared_ptr<core::Object>(
            new core::Object(0, "test1"));

    QPolygon hitbox;
    hitbox.append(QPoint(-100, 0));
    hitbox.append(QPoint(0, 100));
    hitbox.append(QPoint(100, 0));

    object->setHitbox(hitbox);
    object->setPosition(QPointF(2000, 1000));
    object->getAttributes().push_back(
            std::shared_ptr<core::Moving>(new core::Moving(QVector2D(1, 1), 500, 500)));
    object->getStrategies().push_back("moveStrategy");

    std::shared_ptr<core::Object> object2 = std::shared_ptr<core::Object>(
            new core::Object(1, "test2"));

    QPolygon hitbox2;
    hitbox2.append(QPoint(-50, 0));
    hitbox2.append(QPoint(0, 50));
    hitbox2.append(QPoint(50, 0));
    hitbox2.append(QPoint(0, -50));

    object2->setHitbox(hitbox2);
    object2->setPosition(QPointF(3000, 2000));

    engine->getGameWorld()->getObjects().insert(0, object);
    engine->getGameWorld()->getObjects().insert(1, object2);
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
