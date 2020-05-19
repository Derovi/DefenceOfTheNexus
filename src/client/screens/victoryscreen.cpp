#include <QCoreApplication>
#include <QtWidgets/QPushButton>
#include <QtGui/QFontDatabase>
#include <QtWidgets/QFileDialog>

#include "../../utils/lang.h"
#include "../../utils/serializer.h"
#include "../widgets/imagebutton.h"
#include "../app.h"
#include "../widgets/textedit.h"

#include "victoryscreen.h"
#include "gamescreen.h"
#include "optionsscreen.h"
#include "connectionscreen.h"
#include "networkscreen.h"
#include "gamecreationscreen.h"
#include "menuscreen.h"


void client::VictoryScreen::onPaused() {

}

void client::VictoryScreen::onResumed() {

}

client::VictoryScreen::VictoryScreen(): Screen() {
    setBackground(Sprite(QPixmap(":/backgrounds/victory"), 1, 1));

    auto gameName = new TextView(QPoint(1600, 1154), "::victory",
                                 App::getInstance()->getFont());
    gameName->setColor(QColor(249, 192, 6));
    gameName->setTextSize(200);
    addChild(gameName);

    auto menuButton = new ImageButton(QPoint(1520, 1830), 232, 921);
    menuButton->setImage(QImage(":/interface/button"));
    menuButton->setHoverImage(QImage(":/interface/button-hover"));
    menuButton->setHoverWidth(1329);
    menuButton->
            setTextChildren(
            std::make_shared<TextView>(QPoint(0, 0), "::exit_menu",
                                       App::getInstance()->getFont())
    );
    menuButton->getTextChildren()->setColor(QColor(249, 192, 6));
    menuButton->setOnClick([=](QPoint point, bool leftButton) {
        App::getInstance()->openScreen(std::make_shared<MenuScreen>());
    });

    addChild(menuButton);

}
