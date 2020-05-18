#include <QCoreApplication>
#include <QtWidgets/QPushButton>
#include <QtGui/QFontDatabase>

#include "../../utils/lang.h"
#include "../widgets/imagebutton.h"
#include "../app.h"
#include "../properties.h"
#include "../widgets/textview.h"
#include "../widgets/chooser.h"
#include "gamecreationscreen.h"
#include "../widgets/textedit.h"
#include "selectionscreen.h"


void client::GameCreationScreen::onPaused() {

}

void client::GameCreationScreen::onResumed() {

}


client::GameCreationScreen::GameCreationScreen() {
    setBackground(Sprite(QPixmap(":/backgrounds/menu"), 1, 1));

    auto settingName = new TextView(QPoint(1458, 432), "Настройки",
                                    App::getInstance()->getFont());
    settingName->setColor(QColor(249, 192, 6));
    settingName->setTextSize(180);
    addChild(settingName);

    auto playersChooser = new Chooser(QPoint(500, 990), 232, 1260);
    playersChooser->getTextView()->setFont(App::getInstance()->getFont());
    playersChooser->getTextView()->setColor(QColor(249, 192, 6));
    playersChooser->setBackground(QImage(":/interface/chooser"));
    playersChooser->getLeftButton()->setImage(QImage(":/interface/left-button"));
    playersChooser->getLeftButton()->setHoverImage(QImage(":/interface/left-button-hover"));
    playersChooser->getLeftButton()->setHoverWidth(150);
    playersChooser->getLeftButton()->setHoverHeight(232);
    playersChooser->getRightButton()->setImage(QImage(":/interface/right-button"));
    playersChooser->getRightButton()->setHoverImage(QImage(":/interface/right-button-hover"));
    playersChooser->getRightButton()->setHoverWidth(150);
    playersChooser->getRightButton()->setHoverHeight(232);
    playersChooser->setTextWidth(921);
    playersChooser->setButtonWidth(138);
    QStringList playersOptions = {"1 игрок", "2 игрока", "3 игрока", "4 игрока", "5 игроков",
                                  "6 игроков"};
    playersChooser->setOptions(playersOptions);
    addChild(playersChooser);

    auto mapSizeChooser = new Chooser(QPoint(2000, 990), 232, 1260);
    mapSizeChooser->getTextView()->setFont(App::getInstance()->getFont());
    mapSizeChooser->getTextView()->setColor(QColor(249, 192, 6));
    mapSizeChooser->setBackground(QImage(":/interface/chooser"));
    mapSizeChooser->getLeftButton()->setImage(QImage(":/interface/left-button"));
    mapSizeChooser->getLeftButton()->setHoverImage(QImage(":/interface/left-button-hover"));
    mapSizeChooser->getLeftButton()->setHoverWidth(150);
    mapSizeChooser->getLeftButton()->setHoverHeight(232);
    mapSizeChooser->getRightButton()->setImage(QImage(":/interface/right-button"));
    mapSizeChooser->getRightButton()->setHoverImage(QImage(":/interface/right-button-hover"));
    mapSizeChooser->getRightButton()->setHoverWidth(150);
    mapSizeChooser->getRightButton()->setHoverHeight(232);
    mapSizeChooser->setTextWidth(921);
    mapSizeChooser->setButtonWidth(138);
    QStringList mapSizeOptions = {"Маленькая карта", "Средняя карта", "Большая карта"};
    mapSizeChooser->setOptions(mapSizeOptions);
    addChild(mapSizeChooser);

    auto connectButton = new ImageButton(QPoint(700, 1744), 232, 921);
    connectButton->setImage(QImage(":/interface/button"));
    connectButton->setHoverImage(QImage(":/interface/button-hover"));
    connectButton->setHoverWidth(1329);
    connectButton->setTextChildren(
            std::make_shared<TextView>(QPoint(0, 0), "Начать",
                                       App::getInstance()->getFont()));
    connectButton->getTextChildren()->setColor(QColor(249, 192, 6));
    connectButton->getTextChildren()->setTextSize(80);
    connectButton->setOnClick([=](QPoint point, bool leftButton) {
        App::getInstance()->openScreen(std::make_shared<SelectionScreen>(6));
    });

    addChild(connectButton);

    auto backButton = new ImageButton(QPoint(2200, 1744), 232, 921);
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

