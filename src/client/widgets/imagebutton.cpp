#include <QDebug>

#include "imagebutton.h"

client::ImageButton::ImageButton(QPoint position, int height, int width):
        Widget(position), hoverHeight(height), hoverWidth(width) {
    setHeight(height);
    setWidth(width);
}

void client::ImageButton::paint(QPainter& painter) {

    if (is_hovered && !hoverImage.isNull()) {
        painter.drawImage(QRect(boundsRect().center().x() - hoverWidth / 2,
                                boundsRect().center().y() - hoverHeight / 2,
                                hoverWidth,
                                hoverHeight),
                          hoverImage);
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

const std::shared_ptr<client::TextView>& client::ImageButton::getTextChildren() const {
    return textChildren;
}

void client::ImageButton::setTextChildren(const std::shared_ptr<TextView>& textChildren) {
    ImageButton::textChildren = textChildren;
}

int client::ImageButton::getHoverWidth() const {
    return hoverWidth;
}

void client::ImageButton::setHoverWidth(int hoverWidth) {
    ImageButton::hoverWidth = hoverWidth;
}

int client::ImageButton::getHoverSize() const {
    return hoverHeight;
}

void client::ImageButton::setHoverSize(int hoverSize) {
    ImageButton::hoverHeight = hoverSize;
}
