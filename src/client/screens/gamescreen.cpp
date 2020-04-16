#include "../mainwindow.h"
#include "gamescreen.h"
#include "../widgets/gamemap.h"
#include "../widgets/imagebutton.h"
#include "../../server/engine.h"

void client::GameScreen::onPaused() {

}

void client::GameScreen::onResumed() {

}

client::GameScreen::GameScreen() {
    GameMap* gameMap = new GameMap();
    addChild(gameMap);

    ImageButton* closeButton = new ImageButton(QPoint(24, 24), 72, 72);
    closeButton->setImage(QImage(":/images/cancel"));
    closeButton->setOnClick([=](QPoint point) {
        MainWindow::getInstance()->closeScreen();
    });

    addChild(closeButton);

    GameConfiguration gameConfiguration;
    auto* engine = new server::Engine(gameConfiguration);
    std::shared_ptr<core::Object> object = std::shared_ptr<core::Object>(
            new core::Object(0, "test"));

    QPolygon hitbox;
    hitbox.append(QPoint(-100,0));
    hitbox.append(QPoint(0,100));
    hitbox.append(QPoint(100,0));

    object->setHitbox(hitbox);
    object->setPosition(QPointF(1000,1000));

    engine->getGameWorld()->getObjects().insert(0, object);
    gameMap->setGameWorld(engine->getGameWorld());
    engine->start();
}
