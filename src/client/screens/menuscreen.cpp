#include <QCoreApplication>
#include <QtWidgets/QPushButton>
#include <QtGui/QFontDatabase>

#include "../../utils/lang.h"
#include "../widgets/imagebutton.h"
#include "../mainwindow.h"
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

    int fontId = QFontDatabase::addApplicationFont(":/fonts/pacifico");
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont font(fontFamily);
    font.setPixelSize(100);

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
            std::make_shared<TextView>(QPoint(0, 0), utils::Lang::get("start"), font));
    startButton->getTextChildren()->setColor(QColor(249,192,6));
    startButton->setOnClick([=](QPoint point) {
        MainWindow::getInstance()->openScreen(std::make_shared<GameScreen>());
    });

    addChild(startButton);

    auto optionsButton = new ImageButton(QPoint(1510, 1210), 232, 921);
    optionsButton->setImage(QImage(":/interface/button"));
    optionsButton->setHoverImage(QImage(":/interface/button-hover"));
    optionsButton->setHoverWidth(1329);
    optionsButton->setOnClick([=](QPoint point) {
        MainWindow::getInstance()->openScreen(std::make_shared<OptionsScreen>());
    });

    addChild(optionsButton);

    auto exitButton = new ImageButton(QPoint(1510, 1472), 232, 921);
    exitButton->setImage(QImage(":/interface/button"));
    exitButton->setHoverImage(QImage(":/interface/button-hover"));
    exitButton->setHoverWidth(1329);
    exitButton->setOnClick([=](QPoint point) {
        MainWindow::getInstance()->getUiThread()->terminate();
        QCoreApplication::quit();
    });

    addChild(exitButton);

    auto textView = new TextView(QPoint(1000, 1008), utils::Lang::get("example"),
                                 QApplication::font(),
                                 Qt::blue);


    textView->setFont(fontFamily);


    textView->setTextSize(50);

    addChild(textView);
}
