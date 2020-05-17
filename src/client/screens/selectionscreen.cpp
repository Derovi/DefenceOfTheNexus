#include <QCoreApplication>
#include <QtWidgets/QPushButton>
#include <QtGui/QFontDatabase>

#include "../../utils/lang.h"
#include "../widgets/imagebutton.h"
#include "../app.h"
#include "../properties.h"
#include "../widgets/textview.h"
#include "../widgets/chooser.h"
#include "selectionscreen.h"
#include "../widgets/textedit.h"


void client::SelectionScreen::onPaused() {

}

void client::SelectionScreen::onResumed() {

}


client::SelectionScreen::SelectionScreen() {
    setBackground(Sprite(QPixmap(":/backgrounds/menu"), 1, 1));

    auto serverName = new TextView(QPoint(920, 208), "Подключение к серверу",
                                   App::getInstance()->getFont());
    serverName->setColor(QColor(249, 192, 6));
    serverName->setTextSize(180);
    addChild(serverName);

    auto nickName = new TextView(QPoint(1118, 474), "Имя:",
                                 App::getInstance()->getFont());
    nickName->setColor(QColor(249, 192, 6));
    nickName->setTextSize(120);
    addChild(nickName);

    auto nickEdit = new TextEdit(QPoint(1600, 320), 232, 920);
    nickEdit->setBackgroundImage(QImage(":/interface/chooser"));
    nickEdit->setSelectedImage(QImage(":/interface/selected"));
    nickEdit->setTextChildren(std::make_shared<TextView>(QPoint(0, 0), "",
                                                         App::getInstance()->getFont()));
    nickEdit->getTextChildren()->setColor(QColor(249, 192, 6));
    nickEdit->setValidate([](QString text){
        return true;
    });
    addChild(nickEdit);

    auto teamName = new TextView(QPoint(1296, 730), "Выберите команду",
                                 App::getInstance()->getFont());
    teamName->setColor(QColor(249, 192, 6));
    teamName->setTextSize(120);
    addChild(teamName);


    auto connectButton = new ImageButton(QPoint(514, 1876), 232, 921);
    connectButton->setImage(QImage(":/interface/button"));
    connectButton->setHoverImage(QImage(":/interface/button-hover"));
    connectButton->setHoverWidth(1329);
    connectButton->setTextChildren(
            std::make_shared<TextView>(QPoint(0, 0), "Подключиться",
                                       App::getInstance()->getFont()));
    connectButton->getTextChildren()->setColor(QColor(249, 192, 6));
    connectButton->getTextChildren()->setTextSize(80);
    connectButton->setOnClick([=](QPoint point, bool leftButton) {
        QThread* thread = QThread::create([&] {
            QThread::msleep(1);
            App::runOnUiThread([&] {
                App::getInstance()->closeScreen();
            });
        });
        thread->start();
    });

    addChild(connectButton);

    auto backButton = new ImageButton(QPoint(2254, 1876), 232, 921);
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

