#include <QCoreApplication>
#include <QtWidgets/QPushButton>
#include <QtGui/QFontDatabase>

#include "../../utils/lang.h"
#include "../widgets/imagebutton.h"
#include "../app.h"
#include "../properties.h"
#include "../widgets/textview.h"

#include "menuscreen.h"
#include "gamescreen.h"
#include "optionsscreen.h"

void client::MenuScreen::onPaused() {

}

void client::MenuScreen::onResumed() {

}

client::MenuScreen::MenuScreen(): Screen() {
    setBackground(Sprite(QPixmap(":/backgrounds/menu"), 1, 1));

    auto fullScreenButton = new ImageButton(QPoint(408, 24), 72, 72);
    fullScreenButton->setImage(QImage(":/images/fullScreen"));
    fullScreenButton->setOnClick([=](QPoint point) {
        if (properties::fullscreen) {
            properties::fullscreen = false;
            fullScreenButton->setImage(QImage(":/images/fullScreen"));
        } else {
            properties::fullscreen = true;
            fullScreenButton->setImage(QImage(":/images/noFullScreen"));
        }
    });

    addChild(fullScreenButton);

    auto startButton = new ImageButton(QPoint(1510, 948), 232, 921);
    startButton->setImage(QImage(":/interface/button"));
    startButton->setHoverImage(QImage(":/interface/button-hover"));
    startButton->setHoverWidth(1329);
    startButton->setTextChildren(
            std::make_shared<TextView>(QPoint(0, 0), "::start",
                                       App::getInstance()->getFont()));
    startButton->getTextChildren()->setColor(QColor(249, 192, 6));
    startButton->setOnClick([=](QPoint point) {
        App::getInstance()->openScreen(std::make_shared<GameScreen>());
    });

    addChild(startButton);

    auto optionsButton = new ImageButton(QPoint(1510, 1210), 232, 921);
    optionsButton->setImage(QImage(":/interface/button"));
    optionsButton->setHoverImage(QImage(":/interface/button-hover"));
    optionsButton->setHoverWidth(1329);
    optionsButton->setTextChildren(
            std::make_shared<TextView>(QPoint(0, 0), "::options",
                                       App::getInstance()->getFont()));
    optionsButton->getTextChildren()->setColor(QColor(249, 192, 6));
    optionsButton->setOnClick([=](QPoint point) {
        App::getInstance()->openScreen(std::make_shared<OptionsScreen>());
    });

    addChild(optionsButton);

    auto exitButton = new ImageButton(QPoint(1510, 1472), 232, 921);
    exitButton->setImage(QImage(":/interface/button"));
    exitButton->setHoverImage(QImage(":/interface/button-hover"));
    exitButton->setHoverWidth(1329);
    exitButton->setTextChildren(
            std::make_shared<TextView>(QPoint(0, 0), "::exit",
                    App::getInstance()->getFont()));
    exitButton->getTextChildren()->setColor(QColor(249, 192, 6));
    exitButton->setOnClick([=](QPoint point) {
        App::getInstance()->getUiThread()->terminate();
        QCoreApplication::quit();
    });

    addChild(exitButton);
}
