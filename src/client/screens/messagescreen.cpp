
#include "messagescreen.h"
#include <QCoreApplication>
#include <QtWidgets/QPushButton>
#include <QtGui/QFontDatabase>
#include <QtWidgets/QFileDialog>

#include "../../utils/lang.h"
#include "../../utils/serializer.h"
#include "../widgets/imagebutton.h"
#include "../app.h"
#include "../widgets/textedit.h"

#include "gamescreen.h"
#include "optionsscreen.h"
#include "connectionscreen.h"
#include "networkscreen.h"
#include "gamecreationscreen.h"
#include "menuscreen.h"


void client::MessageScreen::onPaused() {

}

void client::MessageScreen::onResumed() {

}

client::MessageScreen::MessageScreen(QString text, MessageType type): Screen() {
    setBackground(Sprite(QPixmap(":/backgrounds/error"), 1, 1));

    auto gameName = new TextView(QPoint(1800, 1154), text,
                                 App::getInstance()->getFont());
    gameName->setColor(QColor(249, 192, 6));
    gameName->setTextSize(180);
    addChild(gameName);

    auto okButton = new ImageButton(QPoint(1520, 1230), 232, 921);
    okButton->setImage(QImage(":/interface/button"));
    okButton->setHoverImage(QImage(":/interface/button-hover"));
    okButton->setHoverWidth(1329);
    okButton->
            setTextChildren(
            std::make_shared<TextView>(QPoint(0, 0), "OK",
                                       App::getInstance()->getFont())
    );
    okButton->getTextChildren()->setColor(QColor(249, 192, 6));
    okButton->setOnClick([=](QPoint point, bool leftButton) {
        App::getInstance()->openScreen(std::make_shared<MenuScreen>());
    });

    addChild(okButton);

}
