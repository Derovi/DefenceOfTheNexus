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
#include "../widgets/playerslot.h"
#include "gamescreen.h"


void client::SelectionScreen::onPaused() {

}

void client::SelectionScreen::onResumed() {

}


client::SelectionScreen::SelectionScreen(std::shared_ptr<MultiplayerInterface> multiplayerInterface,
                                         int playersCount):
        multiplayerInterface(multiplayerInterface), playersCount(playersCount) {
    connect(multiplayerInterface.get(), &MultiplayerInterface::inited, this,
            &SelectionScreen::onInited);

    connect(multiplayerInterface.get(), &MultiplayerInterface::nicknameUpdated,
            this, &SelectionScreen::updatePlayerName);

    connect(multiplayerInterface.get(), &MultiplayerInterface::slotsUpdated,
            this, &SelectionScreen::updateSlots);

    setBackground(Sprite(QPixmap(":/backgrounds/menu"), 1, 1));

    auto serverName = new TextView(QPoint(920, 208), "::connection_to_server",
                                   App::getInstance()->getFont());
    serverName->setColor(QColor(249, 192, 6));
    serverName->setTextSize(180);
    addChild(serverName);

    auto nickName = new TextView(QPoint(1118, 474),
                                 utils::Lang::get("name") + QString(":"),
                                 App::getInstance()->getFont());
    nickName->setColor(QColor(249, 192, 6));
    nickName->setTextSize(120);
    addChild(nickName);

    auto nickEdit = new TextEdit(QPoint(1600, 320), 232, 920);
    nickEdit->setBackgroundImage(QImage(":/interface/chooser"));
    nickEdit->setSelectedImage(QImage(":/interface/selected"));
    nickEdit->setTextChildren(std::make_shared<TextView>(QPoint(0, 0),"",
                                                         App::getInstance()->getFont()));
    nickEdit->getTextChildren()->setColor(QColor(249, 192, 6));
    nickEdit->setValidate([&](const QString& text) {
        QRegExp lettersPattern("^[A-Za-z0-9]+$");
        if (lettersPattern.exactMatch(text) && text.length() < 11){
            requestNicknameChange(text);
            updatePlayerName(QString::number(getMyPlayerId()) + '#' + text);
            return true;
        }
        return false;
    });
    addChild(nickEdit);

    auto teamName = new TextView(QPoint(1296, 730), "::choose_team",
                                 App::getInstance()->getFont());
    teamName->setColor(QColor(249, 192, 6));
    teamName->setTextSize(120);
    addChild(teamName);
    int x = 514;
    for (int i = 0, y = 962; i < playersCount; ++i, y += 304) {
        if (i == 3) {
            x = 2254;
            y = 962;
        }
        auto* playerSlot = new PlayerSlot(QPoint(x, y), 232, 921);
        playerSlot->setImage(QImage(":/interface/free-slot"));
        playerSlot->setHoverImage(QImage(":/interface/busy-slot"));
        playerSlot->setTextChildren(
                std::make_shared<TextView>(QPoint(0, 0), "::free",
                                           App::getInstance()->getFont()));
        playerSlot->getTextChildren()->setColor(QColor(249, 192, 6));
        playerSlot->getTextChildren()->setTextSize(80);
        playerSlot->setOnClick([=](QPoint, bool) {
            requestSlot(i + 1);
        });

        addChild(playerSlot);
        playersSlots.push_back(playerSlot);
    }

    auto connectButton = new ImageButton(QPoint(514, 1876), 232, 921);
    connectButton->setImage(QImage(":/interface/button"));
    connectButton->setHoverImage(QImage(":/interface/button-hover"));
    connectButton->setHoverWidth(1329);
    connectButton->setTextChildren(
            std::make_shared<TextView>(QPoint(0, 0), "::connect",
                                       App::getInstance()->getFont()));
    connectButton->getTextChildren()->setColor(QColor(249, 192, 6));
    connectButton->getTextChildren()->setTextSize(80);
    connectButton->setOnClick([=](QPoint point, bool leftButton) {
        QThread* thread = QThread::create([&] {
            QThread::msleep(1);
            App::runOnUiThread([&] {
                multiplayerInterface->sendInitRequest();
            });
        });
        thread->start();
    });
    addChild(connectButton);

    auto backButton = new ImageButton(QPoint(2254, 1876), 232, 921);
    backButton->setImage(QImage(":/interface/button"));
    backButton->setHoverImage(QImage(":/interface/button-hover"));
    backButton->setHoverWidth(1329);
    backButton->setTextChildren(std::make_shared<TextView>(QPoint(0, 0), "::back",
                                                           App::getInstance()->getFont()));
    backButton->getTextChildren()->setColor(QColor(249, 192, 6));
    backButton->setOnClick([](QPoint point, bool leftButton) {
        //qDebug() << "closing!";
        QThread::create([&] {
            QThread::msleep(1);
            App::runOnUiThread([&] {
                App::getInstance()->closeScreen();
            });
        })->start();
    });
    addChild(backButton);
}

int client::SelectionScreen::getMyPlayerId() {
    return multiplayerInterface->getPlayerId();
}

void client::SelectionScreen::updateSlots(QVector<QString> list) {
    for (auto playerSlot : playersSlots) {
        playerSlot->setPlayerId(255);
        playerSlot->setTaken(false);
    }
    //qDebug() << "size" << list.size() << playersSlots.size();
    for (int i = 0; i < list.size(); ++i) {
        //qDebug() << "upds" << list[i];
        uint8_t id = list[i].left(list[i].indexOf("#") + 1).toInt();
        QString playerName = list[i].mid(list[i].indexOf("#") + 1);
        if (!list[i].isEmpty()) {
            playersSlots[i]->setTaken(true);
            playersSlots[i]->setPlayerId(id);
            updatePlayerName(list[i]);
        } else {
            playersSlots[i]->setTaken(false);
            playersSlots[i]->getTextChildren()->setText("::free");
        }
    }
}

void client::SelectionScreen::requestSlot(uint8_t slotId) {
    multiplayerInterface->requestSlot(slotId);
}

void client::SelectionScreen::requestNicknameChange(const QString& nickname) {
    multiplayerInterface->requestNickname(nickname);
}

void client::SelectionScreen::onInited() {
    //TODO FIX
    App::getInstance()->openScreen(std::make_shared<GameScreen>(multiplayerInterface));
}

void client::SelectionScreen::updatePlayerName(QString text) {
    int playerId = text.left(text.indexOf("#") + 1).toInt();
    QString playerName = text.mid(text.indexOf("#") + 1);
    for (auto playerSlot : playersSlots) {
        if (playerSlot->getPlayerId() == playerId) {
            playerSlot->getTextChildren()->setText(playerName);
        }
    }
}
