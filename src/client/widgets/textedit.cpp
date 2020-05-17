#include <QDebug>

#include <QtCore/QString>
#include "textedit.h"


client::TextEdit::TextEdit(QPoint position, int height, int width):
        Widget(position), selectedHeight(height), selectedWidth(width) {
    setHeight(height);
    setWidth(width);
}

void client::TextEdit::paint(QPainter& painter) {
    if (is_hovered && !selectedImage.isNull()) {
        painter.drawImage(QRect(boundsRect().center().x() - selectedWidth / 2,
                                boundsRect().center().y() - selectedHeight / 2,
                                selectedWidth,
                                selectedHeight),selectedImage);
    } else {
        painter.drawImage(boundsRect(), backgroundImage);
    }
    if (textChildren != nullptr) {
        textChildren->setPosition(getPosition() + QPoint(
                getWidth() / 2.0 - textChildren->getTextWidth() / 2.0,
                getHeght() / 2.0 + textChildren->getTextHeight() / 2.0
        ));
        textChildren->draw();
    }
}


void client::TextEdit::keyPress(QKeyEvent* event) {
    if (is_hovered) {
        QString text = textChildren->getText();
        if (event->key() == Qt::Key_Backspace) {
            text.chop(1);
        } else if (validate != nullptr && validate(text + event->text())) {
            text.append(event->text());
        }
        textChildren->setText(text);
    }

}

const QImage& client::TextEdit::getBackgroundImage() const {
    return backgroundImage;
}

void client::TextEdit::setBackgroundImage(const QImage& backgroundImage) {
    TextEdit::backgroundImage = backgroundImage;
}

const QImage& client::TextEdit::getSelectedImage() const {
    return selectedImage;
}

void client::TextEdit::setSelectedImage(const QImage& selectedImage) {
    TextEdit::selectedImage = selectedImage;
}

const std::shared_ptr<client::TextView>& client::TextEdit::getTextChildren() const {
    return textChildren;
}

void client::TextEdit::setTextChildren(const std::shared_ptr<TextView>& textChildren) {
    TextEdit::textChildren = textChildren;
}

const std::function<bool(QString)>& client::TextEdit::getValidate() const {
    return validate;
}

void client::TextEdit::setValidate(const std::function<bool(QString)>& textChecker) {
    TextEdit::validate = textChecker;
}

int client::TextEdit::getSelectedWidth() const {
    return selectedWidth;
}

void client::TextEdit::setSelectedWidth(int selectedWidth) {
    TextEdit::selectedWidth = selectedWidth;
}

int client::TextEdit::getSelectedHeight() const {
    return selectedHeight;
}

void client::TextEdit::setSelectedHeight(int selectedHeight) {
    TextEdit::selectedHeight = selectedHeight;
}

bool client::TextEdit::isSelected() const {
    return selected;
}

void client::TextEdit::setSelected(bool selected) {
    TextEdit::selected = selected;
}

void client::TextEdit::clicked(QPoint point, bool leftButton) {
    selected = true;
}
