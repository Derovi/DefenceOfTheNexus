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

void client::MenuScreen::onPaused() {

}

void client::MenuScreen::onResumed() {

}

client::MenuScreen::MenuScreen() {
    setBackground(Sprite(QPixmap(":/backgrounds/menu"), 1, 1));
    auto closeButton = new ImageButton(QPoint(24, 24), 72, 72);
    closeButton->setImage(QImage(":/images/cancel"));
    closeButton->setOnClick([=](QPoint point) {
        MainWindow::getInstance()->getUiThread()->terminate();
        QCoreApplication::quit();
    });

    addChild(closeButton);

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

    auto startButton = new ImageButton(QPoint(1000, 100), 500, 500);
    startButton->setImage(QImage(":/images/resume"));
    startButton->setOnClick([=](QPoint point) {
        MainWindow::getInstance()->openScreen(std::shared_ptr<Screen>(new GameScreen()));
    });

    addChild(startButton);

    auto textView = new TextView(QPoint(1000, 50), utils::Lang::get("example"),
                                 QApplication::font(),
                                 Qt::blue);

    int fontId = QFontDatabase::addApplicationFont(":/fonts/pacifico");
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    textView->setFont(fontFamily);


    textView->setTextSize(50);
    textView->setHeight(300);
    textView->setWidth(400);

    addChild(textView);
}
