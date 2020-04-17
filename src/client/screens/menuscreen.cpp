#include <QCoreApplication>
#include <QtWidgets/QPushButton>

#include "menuscreen.h"
#include "gamescreen.h"
#include "../widgets/imagebutton.h"
#include "../mainwindow.h"
#include "../properties.h"

void client::MenuScreen::onPaused() {

}

void client::MenuScreen::onResumed() {

}

client::MenuScreen::MenuScreen() {
    ImageButton * closeButton = new ImageButton(QPoint(24, 24), 72, 72);
    closeButton->setImage(QImage(":/images/cancel"));
    closeButton->setOnClick([=](QPoint point) {
        MainWindow::getInstance()->getUiThread()->terminate();
        QCoreApplication::quit();
    });

    addChild(closeButton);

    ImageButton * fullScreenButton = new ImageButton(QPoint(408, 24), 72, 72);
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

    ImageButton * startButton = new ImageButton(QPoint(1000, 100), 500, 500);
    startButton->setImage(QImage(":/images/resume"));
    startButton->setOnClick([=](QPoint point) {
        MainWindow::getInstance()->openScreen(std::shared_ptr<Screen>(new GameScreen()));
    });

    addChild(startButton);
}
