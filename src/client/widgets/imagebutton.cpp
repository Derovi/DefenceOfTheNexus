#include <QDebug>

#include "imagebutton.h"

client::ImageButton::ImageButton(QPoint position, int height, int width) :
        Widget(position) {
    setHeight(height);
    setWidth(width);
}

void client::ImageButton::paint(QPainter &painter) {
    if (is_hovered && !hoverImage.isNull()) {
        painter.drawImage(boundsRect(), image);
    } else {
        painter.drawImage(boundsRect(), image);
    }
    if (textChildren != nullptr) {
        textChildren->setPosition(getPosition() + QPoint(
                getWidth() / 2.0 - textChildren->getTextWidth() / 2.0,
                getHeght() / 2.0 - textChildren->getTextHeight() / 2.0
                ));
        textChildren->paint(painter);
    }
}

void client::ImageButton::setWidth(int width) {
    this->width = width;
}

void client::ImageButton::setHeight(int height) {
    this->height = height;
}

void client::ImageButton::setImage(QImage image) {
    this->image = image;
}

QImage client::ImageButton::getImage() {
    return image;
}

const QImage& client::ImageButton::getHoverImage() const {
    return hoverImage;
}

void client::ImageButton::setHoverImage(const QImage& hoverImage) {
    ImageButton::hoverImage = hoverImage;
}

const std::shared_ptr<TextView>& client::ImageButton::getTextChildren() const {
    return textChildren;
}

void client::ImageButton::setTextChildren(const std::shared_ptr<TextView>& textChildren) {
    ImageButton::textChildren = textChildren;
}
