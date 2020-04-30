#include <QCoreApplication>
#include <QtWidgets/QPushButton>

#include "../../utils/lang.h"
#include "../widgets/imagebutton.h"
#include "../mainwindow.h"
#include "../properties.h"
#include "../widgets/textview.h"

#include "optionsscreen.h"

void client::OptionsScreen::onPaused() {

}

void client::OptionsScreen::onResumed() {

}

client::OptionsScreen::OptionsScreen() {
    setBackground(Sprite(QPixmap(":/backgrounds/options"), 1, 1));
}
