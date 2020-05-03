#include <QCoreApplication>
#include <QtWidgets/QPushButton>
#include <QtGui/QFontDatabase>

#include "../../utils/lang.h"
#include "../widgets/imagebutton.h"
#include "../app.h"
#include "../properties.h"
#include "../widgets/textview.h"
#include "../widgets/chooser.h"

#include "optionsscreen.h"

void client::OptionsScreen::onPaused() {

}

void client::OptionsScreen::onResumed() {

}

client::OptionsScreen::OptionsScreen(): Screen() {
    setBackground(Sprite(QPixmap(":/backgrounds/menu"), 1, 1));

    auto game_name = new TextView(QPoint(1650, 500), "::options",
                                  App::getInstance()->getFont());
    game_name->setColor(QColor(249, 192, 6));
    game_name->setTextSize(180);
    addChild(game_name);

    auto screenModeChooser = new Chooser(QPoint(1340, 686), 232, 1260);
    screenModeChooser->getTextView()->setFont(App::getInstance()->getFont());
    screenModeChooser->getTextView()->setColor(QColor(249, 192, 6));
    screenModeChooser->setBackground(QImage(":/interface/chooser"));
    screenModeChooser->getLeftButton()->setImage(QImage(":/interface/left-button"));
    screenModeChooser->getLeftButton()->setHoverImage(QImage(":/interface/left-button-hover"));
    screenModeChooser->getLeftButton()->setHoverWidth(150);
    screenModeChooser->getLeftButton()->setHoverHeight(232);
    screenModeChooser->getRightButton()->setImage(QImage(":/interface/right-button"));
    screenModeChooser->getRightButton()->setHoverImage(QImage(":/interface/right-button-hover"));
    screenModeChooser->getRightButton()->setHoverWidth(150);
    screenModeChooser->getRightButton()->setHoverHeight(232);
    screenModeChooser->setTextWidth(921);
    screenModeChooser->setButtonWidth(138);
    screenModeChooser->getOptions().push_back("::full_screen_mode");
    screenModeChooser->getOptions().push_back("::window_screen_mode");
    screenModeChooser->setSelected(properties::fullscreen ? 0 : 1);

    screenModeChooser->setOnChanged([&](int selected) {
        properties::fullscreen = selected == 0;
    });

    addChild(screenModeChooser);

    auto languageChooser = new Chooser(QPoint(1340, 942), 232, 1260);
    languageChooser->getTextView()->setFont(App::getInstance()->getFont());
    languageChooser->getTextView()->setColor(QColor(249, 192, 6));
    languageChooser->setBackground(QImage(":/interface/chooser"));
    languageChooser->getLeftButton()->setImage(QImage(":/interface/left-button"));
    languageChooser->getLeftButton()->setHoverImage(QImage(":/interface/left-button-hover"));
    languageChooser->getLeftButton()->setHoverWidth(150);
    languageChooser->getLeftButton()->setHoverHeight(232);
    languageChooser->getRightButton()->setImage(QImage(":/interface/right-button"));
    languageChooser->getRightButton()->setHoverImage(QImage(":/interface/right-button-hover"));
    languageChooser->getRightButton()->setHoverWidth(150);
    languageChooser->getRightButton()->setHoverHeight(232);
    languageChooser->setTextWidth(921);
    languageChooser->setButtonWidth(138);
    QStringList options;
    int index = 0;
    for (const QString& language : utils::Lang::getLanguages()) {
        if (language == properties::lang) {
            languageChooser->setSelected(index);
        }
        ++index;
        options.push_back(utils::Lang::getTitle(language));
    }
    languageChooser->setOptions(options);
    languageChooser->setOnChanged([&](int selected) {
        properties::lang = utils::Lang::getLanguages()[selected];
        utils::Lang::load(properties::lang, properties::baseLang);
    });
    addChild(languageChooser);

    auto backButton = new ImageButton(QPoint(1510, 1210), 232, 921);
    backButton->setImage(QImage(":/interface/button"));
    backButton->setHoverImage(QImage(":/interface/button-hover"));
    backButton->setHoverWidth(1329);
    backButton->setTextChildren(
            std::make_shared<TextView>(QPoint(0, 0), "::back",
                                       App::getInstance()->getFont()));
    backButton->getTextChildren()->setColor(QColor(249, 192, 6));
    backButton->setOnClick([=](QPoint point) {
        QThread* thread = QThread::create([&] {
            QThread::msleep(1);
            App::getInstance()->closeScreen();
        });
        thread->start();
    });

    addChild(backButton);
}
