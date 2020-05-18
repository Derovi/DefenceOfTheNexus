#include <QCoreApplication>
#include <QtWidgets/QPushButton>
#include <QtGui/QFontDatabase>

#include "../../utils/lang.h"
#include "../widgets/imagebutton.h"
#include "../app.h"
#include "../properties.h"
#include "../widgets/textview.h"
#include "../widgets/chooser.h"
#include "settingsscreen.h"
#include "../widgets/textedit.h"
#include "selectionscreen.h"
#include "../../utils/factory.h"


void client::SettingScreen::onPaused() {

}

void client::SettingScreen::onResumed() {
    server->finish();
    engine->finish();
    server = nullptr;
    engine = nullptr;
}

client::SettingScreen::SettingScreen() {
    setBackground(Sprite(QPixmap(":/backgrounds/menu"), 1, 1));

    auto settingName = new TextView(QPoint(1458, 432), "Настройки",
                                    App::getInstance()->getFont());
    settingName->setColor(QColor(249, 192, 6));
    settingName->setTextSize(180);
    addChild(settingName);

    auto playersNumber = new TextView(QPoint(760, 816), "Число игроков",
                                      App::getInstance()->getFont());
    playersNumber->setColor(QColor(249, 192, 6));
    playersNumber->setTextSize(120);
    addChild(playersNumber);

    auto mapSize = new TextView(QPoint(2258, 816), "Размер карты",
                                App::getInstance()->getFont());
    mapSize->setColor(QColor(249, 192, 6));
    mapSize->setTextSize(120);
    addChild(mapSize);

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
    QStringList options;
    int index = 0;
    for (const QString& language : utils::Lang::getLanguages()) {
        if (language == properties::lang) {
            playersChooser->setSelected(index);
        }
        ++index;
        options.push_back(utils::Lang::getTitle(language));
    }
    playersChooser->setOptions(options);
    playersChooser->setOnChanged([&](int selected) {
        properties::lang = utils::Lang::getLanguages()[selected];
        utils::Lang::load(properties::lang, properties::baseLang);
    });
    addChild(playersChooser);

    auto mapChooser = new Chooser(QPoint(2000, 990), 232, 1260);
    mapChooser->getTextView()->setFont(App::getInstance()->getFont());
    mapChooser->getTextView()->setColor(QColor(249, 192, 6));
    mapChooser->setBackground(QImage(":/interface/chooser"));
    mapChooser->getLeftButton()->setImage(QImage(":/interface/left-button"));
    mapChooser->getLeftButton()->setHoverImage(QImage(":/interface/left-button-hover"));
    mapChooser->getLeftButton()->setHoverWidth(150);
    mapChooser->getLeftButton()->setHoverHeight(232);
    mapChooser->getRightButton()->setImage(QImage(":/interface/right-button"));
    mapChooser->getRightButton()->setHoverImage(QImage(":/interface/right-button-hover"));
    mapChooser->getRightButton()->setHoverWidth(150);
    mapChooser->getRightButton()->setHoverHeight(232);
    mapChooser->setTextWidth(921);
    mapChooser->setButtonWidth(138);
    QStringList optionss;
    int indexx = 0;
    for (const QString& language : utils::Lang::getLanguages()) {
        if (language == properties::lang) {
            mapChooser->setSelected(index);
        }
        ++index;
        options.push_back(utils::Lang::getTitle(language));
    }
    mapChooser->setOptions(options);
    mapChooser->setOnChanged([&](int selected) {
        properties::lang = utils::Lang::getLanguages()[selected];
        utils::Lang::load(properties::lang, properties::baseLang);
    });
    addChild(mapChooser);

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
        startServer();
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

const std::shared_ptr<client::MultiplayerInterface>&
client::SettingScreen::getMultiplayerInterface() const {
    return multiplayerInterface;
}

void client::SettingScreen::startServer() {
    GameConfiguration gameConfiguration;
    engine = std::make_shared<server::Engine>(gameConfiguration);

    engine->getGameWorld()->setTeamCount(2);
    engine->getGameWorld()->summonObject(utils::Factory::getObjectSignature("test1").value(),
                                         QPoint(1800, 1200), 1);

    engine->getGameWorld()->summonObject(
            utils::Factory::getObjectSignature("iron").value(),
            QPoint(842, 1422));

    engine->start();

    server = std::make_shared<server::Server>(engine.get(), 25565);
    server->start();

    multiplayerInterface = std::make_shared<MultiplayerInterface>("127.0.0.1", server->getPort());
    multiplayerInterface->sendInitRequest();
    App::getInstance()->openScreen(std::make_shared<SelectionScreen>(multiplayerInterface));
}

uint8_t client::SettingScreen::getMyPlayerId() {
    return multiplayerInterface->getPlayerId();
}
