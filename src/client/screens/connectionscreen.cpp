#include <QCoreApplication>
#include <QtWidgets/QPushButton>
#include <QtGui/QFontDatabase>

#include "../../utils/lang.h"
#include "../widgets/imagebutton.h"
#include "../app.h"
#include "../properties.h"
#include "../widgets/textview.h"
#include "../widgets/chooser.h"

#include "connectionscreen.h"

void client::ConnectionScreen::onPaused() {}

void client::ConnectionScreen::onResumed() {}

client::ConnectionScreen::ConnectionScreen(): Screen() {
    constructInterface();
    startServer();
    connectServer();
}

void client::ConnectionScreen::constructInterface() {
    setBackground(Sprite(QPixmap(":/backgrounds/menu"), 1, 1));

    auto backButton = new ImageButton(QPoint(1510, 1210), 232, 921);
    backButton->setImage(QImage(":/interface/button"));
    backButton->setHoverImage(QImage(":/interface/button-hover"));
    backButton->setHoverWidth(1329);
    backButton->setTextChildren(
            std::make_shared<TextView>(QPoint(0, 0), "::back",
                                       App::getInstance()->getFont()));
    backButton->getTextChildren()->setColor(QColor(249, 192, 6));
    backButton->setOnClick([=](QPoint point, bool leftButton) {
        QThread* thread = QThread::create([&] {
            QThread::msleep(1);
            App::runOnUiThread([&] {
                App::getInstance()->closeScreen();
            });
        });
        thread->start();
    });

    addChild(backButton);
}

const std::shared_ptr<server::Engine>& client::ConnectionScreen::getEngine() const {
    return engine;
}

const std::shared_ptr<server::Server>& client::ConnectionScreen::getServer() const {
    return server;
}

const QString& client::ConnectionScreen::getAddress() const {
    return address;
}

int client::ConnectionScreen::getPort() const {
    return port;
}

void client::ConnectionScreen::startServer() {
    GameConfiguration gameConfiguration;
    engine = std::make_shared<server::Engine>(gameConfiguration);

    if (gameWorld != nullptr) {
        engine->setGameWorld(gameWorld);
    } else {
        /*engine->getGameWorld()->summonObject(utils::Factory::getObjectSignature("test1").value(),
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
                                          utils::Factory::getObjectSignature("column1").value(), 0);
        engine->getGameWorld()->summonObject(utils::Factory::getObjectSignature("mage").value(),
                                             QPoint(700, 200));
        engine->getGameWorld()->buildWall(QPoint(1000,0),QPoint(1000,300), utils::Factory::getObjectSignature("wall1").value(),
                                          utils::Factory::getObjectSignature("column1").value(), 0);
        engine->getGameWorld()->summonObject(utils::Factory::getObjectSignature("ogre").value(),
                                             QPoint(1200, 200));
        engine->getGameWorld()->buildWall(QPoint(1500,0),QPoint(1500,300), utils::Factory::getObjectSignature("wall1").value(),
                                          utils::Factory::getObjectSignature("column1").value(), 0);
        engine->getGameWorld()->summonObject(utils::Factory::getObjectSignature("scout").value(),
                                             QPoint(1700, 200));
        engine->getGameWorld()->buildWall(QPoint(2000,0),QPoint(2000,300), utils::Factory::getObjectSignature("wall1").value(),
                                          utils::Factory::getObjectSignature("column1").value(), 0);

        engine->getGameWorld()->buildWall(QPoint(0,0),QPoint(0,3000), utils::Factory::getObjectSignature("wall1").value(),
                                          utils::Factory::getObjectSignature("column1").value(), 0);

        engine->getGameWorld()->buildWall(QPoint(0,3000),QPoint(3000,3000), utils::Factory::getObjectSignature("wall1").value(),
                                          utils::Factory::getObjectSignature("column1").value(), 0);

        engine->getGameWorld()->buildWall(QPoint(3000,3000),QPoint(3000,0), utils::Factory::getObjectSignature("wall1").value(),
                                          utils::Factory::getObjectSignature("column1").value(), 0);

        engine->getGameWorld()->buildWall(QPoint(3000,0),QPoint(0,0), utils::Factory::getObjectSignature("wall1").value(),
                                          utils::Factory::getObjectSignature("column1").value(), 0);


        engine->getGameWorld()->summonObject(
                utils::Factory::getObjectSignature("resourcebundle-stone").value(),
                QPoint(2200, 1000));
        engine->getGameWorld()->summonObject(utils::Factory::getObjectSignature("scorpion").value(),
                                             QPoint(2200, 1200));*/
    }

    //gameMap->setShowHitBoxes(true);
    engine->start();

    server = std::make_shared<server::Server>(engine.get(), 25565);
    server->start();

    address = "127.0.0.1";
    port = 25565;
}

void client::ConnectionScreen::connectServer() {
    multiplayerInterface = std::make_shared<MultiplayerInterface>(address, port);
}

void client::ConnectionScreen::joinGame() {
    App::getInstance()->openScreen(std::make_shared<GameScreen>(multiplayerInterface));
}
