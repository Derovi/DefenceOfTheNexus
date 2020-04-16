#include "menuscreen.h"
#include "../widgets/imagebutton.h"
#include "../mainwindow.h"

void client::MenuScreen::onPaused() {

}

void client::MenuScreen::onResumed() {

}

client::MenuScreen::MenuScreen() {
    ImageButton * closeButton = new ImageButton(QPoint(24, 24), 72, 72);
    closeButton->setImage(QImage(":/images/cancel"));
    closeButton->setOnClick([=](QPoint point) {
        MainWindow::getInstance()->close();
    });
    addChild(closeButton);
}
