#include <QDebug>

#include "chooser.h"

client::Chooser::Chooser(QPoint position, int height, int width):
        Widget(position), selected(0), textWidth(width * 3 / 4) {
    setHeight(height);
    setWidth(width);
    int buttonWidth = (width - textWidth) / 2;
    leftButton = std::make_shared<ImageButton>(absolutePosition(), height, buttonWidth);
    leftButton->setOnClick([&](const QPoint& point) {
        leftClick();
    });
    rightButton = std::make_shared<ImageButton>(absolutePosition() + QPoint(width - buttonWidth, 0),
                                                height, buttonWidth);
    rightButton->setOnClick([&](const QPoint& point) {
        rightClick();
    });

    textView = std::make_shared<TextView>(absolutePosition() + QPoint(buttonWidth, 0));
}

void client::Chooser::paint(QPainter& painter) {
    if (!background.isNull()) {
        painter.drawImage(QRect(0,0,width, height), background);
    }
    leftButton->draw();
    rightButton->draw();
    if (!options.empty()) {
        textView->setText(options[selected]);
    }
    textView->draw();
}

void client::Chooser::leftClick() {
    if (options.empty()) {
        return;
    }
    selected = (selected + options.size() - 1) % options.size();
    onChanged(selected);
}

void client::Chooser::rightClick() {
    if (options.empty()) {
        return;
    }
    selected = (selected + 1) % options.size();
    onChanged(selected);
}

int client::Chooser::getSelected() const {
    return selected;
}

const std::shared_ptr<client::ImageButton>& client::Chooser::getLeftButton() const {
    return leftButton;
}

const std::shared_ptr<client::ImageButton>& client::Chooser::getRightButton() const {
    return rightButton;
}

const std::shared_ptr<client::TextView>& client::Chooser::getTextView() const {
    return textView;
}
