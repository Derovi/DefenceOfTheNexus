#include <QCoreApplication>
#include <QtWidgets/QPushButton>
#include <QtGui/QFontDatabase>
#include <QDebug>

#include "../../utils/lang.h"
#include "../widgets/imagebutton.h"
#include "../app.h"
#include "../properties.h"
#include "../widgets/textview.h"
#include "../widgets/chooser.h"
#include "networkscreen.h"
#include "../widgets/textedit.h"
#include "selectionscreen.h"


void client::NetworkScreen::onPaused() {

}

void client::NetworkScreen::onResumed() {

}


client::NetworkScreen::NetworkScreen(): multiplayerInterface(nullptr) {
    setBackground(Sprite(QPixmap(":/backgrounds/menu"), 1, 1));

    auto networkName = new TextView(QPoint(1700, 500), "Сеть",
                                    App::getInstance()->getFont());
    networkName->setColor(QColor(249, 192, 6));
    networkName->setTextSize(180);
    addChild(networkName);

    auto ipName = new TextView(QPoint(1148, 924), "IP-адрес",
                               App::getInstance()->getFont());
    ipName->setColor(QColor(249, 192, 6));
    ipName->setTextSize(120);
    addChild(ipName);

    auto portName = new TextView(QPoint(1216, 1232), "Порт",
                                 App::getInstance()->getFont());
    portName->setColor(QColor(249, 192, 6));
    portName->setTextSize(120);
    addChild(portName);

    ipInput = new TextEdit(QPoint(1772, 780), 232, 920);
    ipInput->setBackgroundImage(QImage(":/interface/chooser"));
    ipInput->setSelectedImage(QImage(":/interface/selected"));
    ipInput->setTextChildren(std::make_shared<TextView>(QPoint(0, 0), "",
                                                        App::getInstance()->getFont()));
    ipInput->getTextChildren()->setColor(QColor(249, 192, 6));
    ipInput->setValidate([](QString text) {
                             QRegExp lettersPattern("[^\\d.]");
                             if (text.isEmpty() || lettersPattern.indexIn(text) != -1) {
                                 return false;
                             }
                             if (text.back() == '.') {
                                 text += '0';
                             }
                             int pointCount = text.count('.');
                             for (int index = 0;
                                  index < 3 - pointCount;
                                  ++index) {
                                 text += ".0";
                             }
                             return matchesIpRegex(text);
                         }
    );
    addChild(ipInput);

    portInput = new TextEdit(QPoint(1772, 1080), 232, 920);
    portInput->setBackgroundImage(QImage(":/interface/chooser"));
    portInput->setSelectedImage(QImage(":/interface/selected"));
    portInput->setTextChildren(std::make_shared<TextView>(QPoint(0, 0), "25565",
                                                          App::getInstance()->getFont()));
    portInput->getTextChildren()->setColor(QColor(249, 192, 6));
    portInput->setValidate([](QString text) {
        return text.toInt() > 0 && text.toInt() < 100'000;
    });
    addChild(portInput);

    auto connectButton = new ImageButton(QPoint(740, 1744), 232, 921);
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
                connectClicked();
            });
        });
        thread->start();
    });

    addChild(connectButton);

    auto backButton = new ImageButton(QPoint(2178, 1744), 232, 921);
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

void client::NetworkScreen::connectClicked() {
    QString ip = ipInput->getTextChildren()->getText();
    if (!matchesIpRegex(ip)) {
        return;
    }
    QString port = portInput->getTextChildren()->getText();
    multiplayerInterface = std::make_shared<MultiplayerInterface>(ip, port.toInt(),
                                                                  MultiplayerInterface::State::CONNECTING_SERVER);
    connect(multiplayerInterface.get(), &MultiplayerInterface::connected, this, [&](int teamCount) {
        App::getInstance()->openScreen(std::make_shared<SelectionScreen>(multiplayerInterface, teamCount));
    });
}

bool client::NetworkScreen::matchesIpRegex(const QString& text) {
    QRegExp ipPattern("^(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\."
                      "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\."
                      "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\."
                      "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$");
    return ipPattern.exactMatch(text);
}

