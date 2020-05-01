#include <QCoreApplication>
#include <QtWidgets/QPushButton>
#include <QtGui/QFontDatabase>

#include "../../utils/lang.h"
#include "../widgets/imagebutton.h"
#include "../mainwindow.h"
#include "../properties.h"
#include "../widgets/textview.h"

#include "optionsscreen.h"
#include "../widgets/chooser.h"

void client::OptionsScreen::onPaused() {

}

void client::OptionsScreen::onResumed() {

}

client::OptionsScreen::OptionsScreen(): Screen() {
    setBackground(Sprite(QPixmap(":/backgrounds/options"), 1, 1));

    int fontId = QFontDatabase::addApplicationFont(":/fonts/pacifico");
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont font(fontFamily);
    font.setPixelSize(100);

    auto languageChooser = new Chooser(QPoint(1306,1210), 232,1329);
    languageChooser->setBackground(QImage(":/sprites/fire"));
    languageChooser->getTextView()->setFont(font);
    addChild(languageChooser);

    auto backButton = new ImageButton(QPoint(1510, 1472), 232, 921);
    backButton->setImage(QImage(":/interface/button"));
    backButton->setHoverImage(QImage(":/interface/button-hover"));
    backButton->setHoverWidth(1329);
    backButton->setTextChildren(
            std::make_shared<TextView>(QPoint(0, 0), utils::Lang::get("back"), font));
    backButton->getTextChildren()->setColor(QColor(249,192,6));
    backButton->setOnClick([=](QPoint point) {
        QThread* thread = QThread::create([&] {
            QThread::msleep(1);
            MainWindow::getInstance()->closeScreen();
        });
        thread->start();
    });

    addChild(backButton);
}
