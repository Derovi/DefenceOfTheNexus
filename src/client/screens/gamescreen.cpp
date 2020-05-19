#include <QDebug>

#include "gamescreen.h"

#include "../app.h"
#include "../widgets/gamemap.h"
#include "../widgets/imagebutton.h"
#include "../../server/engine.h"
#include "../../core/attributes/moving.h"
#include "../../utils/factory.h"
#include "../network/multiplayerinterface.h"

#include "pausescreen.h"

void client::GameScreen::onPaused() {
    paused = true;
}

void client::GameScreen::onResumed() {
    paused = false;
    setLastPaintTime(std::chrono::steady_clock::now());
}

void client::GameScreen::draw() {
    Screen::draw();
    int teamNumber = getTeam();
    int unitId = getInterface()->getSelectedUnitId();
    if (gameMap->getGameWorld()->getObjects().contains(unitId)) {
        teamNumber = gameMap->getGameWorld()->getObjects()[unitId]->getTeam();
    }
    teamButton->getTextChildren()->setText(QString::number(teamNumber));
    if (teamNumber == getTeam()) {
        teamButton->getTextChildren()->setColor(Qt::green);
    } else {
        teamButton->getTextChildren()->setColor(Qt::red);
    }
}

client::GameMap* client::GameScreen::getGameMap() const {
    return gameMap;
}

client::GameInterface* client::GameScreen::getInterface() const {
    return interface;
}

client::GameScreen::GameScreen(const std::shared_ptr<MultiplayerInterface>& multiplayerInterface):
        Screen(), paused(false) {
    this->multiplayerInterface = multiplayerInterface;
    //qDebug() << "game screen start";
    gameMap = new GameMap();
    gameMap->setDisplayBounds(QRect(1920, 1080, 1920, 1080));
    Sprite background(QPixmap(":/sprites/background"), 1, 1, 0);
    gameMap->setBackground(background);
    addChild(gameMap);
    auto pauseButton = new ImageButton(QPoint(24, 24), 72, 72);
    pauseButton->setImage(QImage(":/images/cancel"));
    pauseButton->setOnClick([=](QPoint point, bool leftButton) {
        App::getInstance()->openScreen(std::make_shared<PauseScreen>());
        //qDebug() << "Сервер запущен на порту: " << QString::number(multiplayerInterface->getPort());
    });

    addChild(pauseButton);

    teamButton = new ImageButton(QPoint(3734, 24), 72, 72);
    teamButton->setImage(QImage(":/interface/icon-slot"));
    teamButton->setTextChildren(
            std::make_shared<TextView>(QPoint(0, 0), QString::number(multiplayerInterface->getTeam()),
                                                            App::getInstance()->getFont()));
    teamButton->getTextChildren()->setTextSize(50);
    teamButton->getTextChildren()->setColor(QColor(255, 255, 255));
    addChild(teamButton);

    gameMap->setGameWorld(multiplayerInterface->getGameWorld());
    interface = new GameInterface(QPoint(152, 1710), 3536, 450, gameMap->getGameWorld());
    addChild(interface);
    //qDebug() << "game screen started";
}

const std::shared_ptr<server::Engine>& client::GameScreen::getEngine() const {
    return engine;
}

client::GameScreen::~GameScreen() {
    if (engine) {
        engine->finish();
    }
}

uint8_t client::GameScreen::getTeam() const {
    //qDebug() << "team: " << multiplayerInterface->getTeam() << gameMap->getGameWorld()->getTeamCount();
    return multiplayerInterface->getTeam();
}

const std::shared_ptr<client::MultiplayerInterface>& client::GameScreen::getMultiplayerInterface() const {
    return multiplayerInterface;
}
