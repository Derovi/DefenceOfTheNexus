
#include "lossscreen.h"
#include <QCoreApplication>
#include <QtWidgets/QPushButton>
#include <QtGui/QFontDatabase>
#include <QtWidgets/QFileDialog>

#include "../../utils/lang.h"
#include "../../utils/serializer.h"
#include "../widgets/imagebutton.h"
#include "../app.h"
#include "../widgets/textedit.h"

#include "optionsscreen.h"
#include "connectionscreen.h"
#include "networkscreen.h"
#include "gamecreationscreen.h"
#include "menuscreen.h"


void client::LossScreen::onPaused() {

}

void client::LossScreen::onResumed() {

}

client::LossScreen::LossScreen(): Screen() {
    setBackground(Sprite(QPixmap(":/backgrounds/lose"), 1, 1));

    auto gameName = new TextView(QPoint(1300, 1154), "::game_over",
                                 App::getInstance()->getFont());
    gameName->setColor(QColor(249, 192, 6));
    gameName->setTextSize(200);
    addChild(gameName);

    auto loadGameButton = new ImageButton(QPoint(600, 1830), 232, 921);
    loadGameButton->setImage(QImage(":/interface/button"));
    loadGameButton->setHoverImage(QImage(":/interface/button-hover"));
    loadGameButton->setHoverWidth(1329);
    loadGameButton->setTextChildren(
            std::make_shared<TextView>(QPoint(0, 0), "::load_game",
                                       App::getInstance()->getFont()));
    loadGameButton->getTextChildren()->setColor(QColor(249, 192, 6));
    loadGameButton->setOnClick([=](QPoint point, bool leftButton) {
        QString fileName =
                QFileDialog::getOpenFileName(App::getInstance(),
                                             utils::Lang::get("save_game"), ".gsv", "(*.gsv)");
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            return;
        }

        utils::Serializer serializer;
        std::shared_ptr<core::GameWorld> gameWorld;
        QTextStream stream(&file);
        auto deserialized = serializer.deserializeGameWorld(stream.readAll());
        file.close();

        if (deserialized == std::nullopt) {
            return;
        }

        gameWorld = std::make_shared<core::GameWorld>(deserialized.value());

//!TODO fix saving
//App::getInstance()->openScreen(std::make_shared<GameScreen>(gameWorld));
    });

    addChild(loadGameButton);

    auto menuButton = new ImageButton(QPoint(2320, 1830), 232, 921);
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
