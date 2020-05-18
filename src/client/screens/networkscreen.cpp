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


void client::NetworkScreen::onPaused() {

}

void client::NetworkScreen::onResumed() {

}


client::NetworkScreen::NetworkScreen() {
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

    auto ipEdit = new TextEdit(QPoint(1772, 780), 232, 920);
    ipEdit->setBackgroundImage(QImage(":/interface/chooser"));
    ipEdit->setSelectedImage(QImage(":/interface/selected"));
    ipEdit->setTextChildren(std::make_shared<TextView>(QPoint(0, 0), "",
                                                       App::getInstance()->getFont()));
    ipEdit->getTextChildren()->setColor(QColor(249, 192, 6));
    ipEdit->setValidate([](QString text) {
                            QRegExp lettersPattern("[^\\d.]");
                            if (text.isEmpty() || lettersPattern.indexIn(text) != -1) {
                                return false;
                            }
                            if (text.back() == '.') {
                                text += '0';
                            }
                            int pointCount = text.count('.');
                            for (int index = 0; index < 3 - pointCount; ++index) {
                                text += ".0";
                            }
                            QRegExp ipPattern("^^(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\."
                                              "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\."
                                              "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\."
                                              "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$");
                            return ipPattern.exactMatch(text);
                        }
    );
    addChild(ipEdit);

    auto portEdit = new TextEdit(QPoint(1772, 1080), 232, 920);
    portEdit->setBackgroundImage(QImage(":/interface/chooser"));
    portEdit->setSelectedImage(QImage(":/interface/selected"));
    portEdit->setTextChildren(std::make_shared<TextView>(QPoint(0, 0), "25565",
                                                         App::getInstance()->getFont()));
    portEdit->getTextChildren()->setColor(QColor(249, 192, 6));
    portEdit->setValidate([](QString text) {
        return text.toInt() > 0 && text.toInt() < 100'000;
    });
    addChild(portEdit);

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
                App::getInstance()->closeScreen();
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

