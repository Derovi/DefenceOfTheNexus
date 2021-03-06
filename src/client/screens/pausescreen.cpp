#include <QCoreApplication>
#include <QtWidgets/QPushButton>
#include <QtGui/QFontDatabase>
#include <QtWidgets/QFileDialog>

#include "../../utils/lang.h"
#include "../../utils/serializer.h"
#include "../../utils/smartserializer.h"
#include "../widgets/imagebutton.h"
#include "../app.h"
#include "../properties.h"
#include "../widgets/textview.h"

#include "pausescreen.h"
#include "optionsscreen.h"
#include "gamescreen.h"

void client::PauseScreen::onPaused() {

}

void client::PauseScreen::onResumed() {

}

client::PauseScreen::PauseScreen(): Screen() {
    setBackground(Sprite(QPixmap(":/backgrounds/pause"), 1, 1));

    auto game_name = new TextView(QPoint(1700, 500), "::pause",
                                  App::getInstance()->getFont());
    game_name->setColor(QColor(249, 192, 6));
    game_name->setTextSize(180);
    addChild(game_name);

    auto resumeButton = new ImageButton(QPoint(1510, 686), 232, 921);
    resumeButton->setImage(QImage(":/interface/button"));
    resumeButton->setHoverImage(QImage(":/interface/button-hover"));
    resumeButton->setHoverWidth(1329);
    resumeButton->setTextChildren(
            std::make_shared<TextView>(QPoint(0, 0), "::resume",
                                       App::getInstance()->getFont()));
    resumeButton->getTextChildren()->setColor(QColor(249, 192, 6));
    resumeButton->setOnClick([=](QPoint point, bool leftButton) {
        QThread* thread = QThread::create([&] {
            QThread::msleep(1);
            App::runOnUiThread([&] {
                App::getInstance()->closeScreen();
            });
        });
        thread->start();
    });

    addChild(resumeButton);

    auto saveGameButton = new ImageButton(QPoint(1510, 942), 232, 921);
    saveGameButton->setImage(QImage(":/interface/button"));
    saveGameButton->setHoverImage(QImage(":/interface/button-hover"));
    saveGameButton->setHoverWidth(1329);
    saveGameButton->setTextChildren(
            std::make_shared<TextView>(QPoint(0, 0), "::save_game",
                                       App::getInstance()->getFont()));
    saveGameButton->getTextChildren()->setColor(QColor(249, 192, 6));
    saveGameButton->setOnClick([=](QPoint point, bool leftButton) {
        QString fileName = QFileDialog::getSaveFileName(App::getInstance(),
                                                        utils::Lang::get("save_game"), ".gsv",
                                                        "(*.gsv)");

        core::GameWorld* gameWorld = nullptr;
        for (std::shared_ptr<Screen>& screen : App::getInstance()->getScreens()) {
            auto* gameScreen = dynamic_cast<GameScreen*>(screen.get());
            if (gameScreen) {
                gameWorld = gameScreen->getGameMap()->getGameWorld().get();
            }
        }

        if (!gameWorld) {
            return;
        }

        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
            return;
        }

        utils::Serializer serializer;
        serializer.setPrettyPrinting(true);
//        utils::SmartSerializer smartSerializer(false);

        QTextStream stream(&file);
        core::GameWorld copy = *gameWorld;
        std::ofstream cout("output.txt");
        for(auto& it:copy.getObjects()){
            it->setPosition(QPointF(42,42));
            cout<<it->getPosition().x();
        }
        file.close();
    });

    addChild(saveGameButton);

    auto optionsButton = new ImageButton(QPoint(1510, 1210), 232, 921);
    optionsButton->setImage(QImage(":/interface/button"));
    optionsButton->setHoverImage(QImage(":/interface/button-hover"));
    optionsButton->setHoverWidth(1329);
    optionsButton->setTextChildren(
            std::make_shared<TextView>(QPoint(0, 0), "::options",
                                       App::getInstance()->getFont()));
    optionsButton->getTextChildren()->setColor(QColor(249, 192, 6));
    optionsButton->setOnClick([=](QPoint point, bool leftButton) {
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
    exitButton->setOnClick([=](QPoint point, bool leftButton) {
        QThread* thread = QThread::create([&] {
            QThread::msleep(1);
            App::runOnUiThread([&] {
                App::getInstance()->closeScreen();
                App::getInstance()->closeScreen();
                App::getInstance()->closeScreen();
            });
        });
        thread->start();
    });

    addChild(exitButton);
}
