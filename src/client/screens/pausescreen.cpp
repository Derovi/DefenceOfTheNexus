#include <QCoreApplication>
#include <QtWidgets/QPushButton>
#include <QtGui/QFontDatabase>

#include "../../utils/lang.h"
#include "../widgets/imagebutton.h"
#include "../app.h"
#include "../properties.h"
#include "../widgets/textview.h"

#include "pausescreen.h"
#include "optionsscreen.h"

void client::PauseScreen::onPaused() {

}

void client::PauseScreen::onResumed() {

}

client::PauseScreen::PauseScreen() : Screen() {
    setBackground(Sprite(QPixmap(":/backgrounds/pause"), 1, 1));

    auto game_name = new TextView(QPoint(1700, 800), "::pause",
                                  App::getInstance()->getFont());
    game_name->setColor(QColor(249, 192, 6));
    game_name->setTextSize(180);
    addChild(game_name);

    auto resumeButton = new ImageButton(QPoint(1510, 948), 232, 921);
    resumeButton->setImage(QImage(":/interface/button"));
    resumeButton->setHoverImage(QImage(":/interface/button-hover"));
    resumeButton->setHoverWidth(1329);
    resumeButton->setTextChildren(
            std::make_shared<TextView>(QPoint(0, 0), "::resume",
                                       App::getInstance()->getFont()));
    resumeButton->getTextChildren()->setColor(QColor(249, 192, 6));
    resumeButton->setOnClick([=](QPoint point) {
        QThread* thread = QThread::create([&] {
            QThread::msleep(1);
            App::getInstance()->closeScreen();
        });
        thread->start();
    });

    addChild(resumeButton);

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
            std::make_shared<TextView>(QPoint(0, 0), "::exit_menu",
                                       App::getInstance()->getFont()));
    exitButton->getTextChildren()->setColor(QColor(249, 192, 6));
    exitButton->setOnClick([=](QPoint point) {
        QThread* thread = QThread::create([&] {
            QThread::msleep(1);
            App::getInstance()->closeScreen();
            App::getInstance()->closeScreen();
        });
        thread->start();
    });

    addChild(exitButton);
}
