#include <QDebug>
#include <QtCore/QPoint>

#include "chooser.h"

client::Chooser::Chooser(QPoint position, int height, int width):
        Widget(position), selected(0), textWidth(width * 3 / 4) {
    setHeight(height);
    setWidth(width);

    leftButton = new ImageButton();
    leftButton->setOnClick([&](const QPoint& point, bool leftButton) {
        leftClick();
    });

    rightButton = new ImageButton();
    rightButton->setOnClick([&](const QPoint& point, bool leftButton) {
        rightClick();
    });

    textView = new TextView();

    addChild(leftButton);

    addChild(rightButton);

    addChild(textView);

    update();
}

void client::Chooser::setSelected(int selected) {
    Chooser::selected = selected;
}

void client::Chooser::paint(QPainter& painter) {
    if (!background.isNull()) {
        painter.drawImage(QRect((width - textWidth) / 2, 0, textWidth, height), background);
    }
    if (!options.empty()) {
        textView->setText(options[selected]);
    }
    update();
}

void client::Chooser::leftClick() {
    if (options.empty()) {
        return;
    }
    selected = (selected + options.size() - 1) % options.size();
    if (onChanged) {
        onChanged(selected);
    }
}

void client::Chooser::rightClick() {
    if (options.empty()) {
        return;
    }
    selected = (selected + 1) % options.size();
    if (onChanged) {
        onChanged(selected);
    }
}

int client::Chooser::getSelected() const {
    return selected;
}

const QImage& client::Chooser::getBackground() const {
    return background;
}

void client::Chooser::setBackground(const QImage& background) {
    Chooser::background = background;
}

const std::function<void(int)>& client::Chooser::getOnChanged() const {
    return onChanged;
}

void client::Chooser::setOnChanged(const std::function<void(int)>& onChanged) {
    Chooser::onChanged = onChanged;
}

const QStringList& client::Chooser::getOptions() const {
    return options;
}

void client::Chooser::setOptions(const QStringList& options) {
    Chooser::options = options;
}

int client::Chooser::getTextWidth() const {
    return textWidth;
}

void client::Chooser::setTextWidth(int textWidth) {
    Chooser::textWidth = textWidth;
    update();
}

int client::Chooser::getButtonWidth() const {
    return buttonWidth;
}

void client::Chooser::setButtonWidth(int buttonWidth) {
    Chooser::buttonWidth = buttonWidth;
    update();
}

void client::Chooser::update() {
    leftButton->setWidth(buttonWidth);
    leftButton->setHeight(height);

    rightButton->setPosition(QPoint(width - buttonWidth, 0));
    rightButton->setWidth(buttonWidth);
    rightButton->setHeight(height);

    textView->setPosition(QPoint(
            getWidth() / 2.0 - textView->getTextWidth() / 2.0,
            getHeght() / 2.0 + textView->getTextHeight() / 2.0
    ));
}

client::ImageButton* client::Chooser::getLeftButton() const {
    return leftButton;
}

client::ImageButton* client::Chooser::getRightButton() const {
    return rightButton;
}

client::TextView* client::Chooser::getTextView() const {
    return textView;
}

QStringList& client::Chooser::getOptions() {
    return options;
}
