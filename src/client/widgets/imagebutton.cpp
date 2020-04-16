#include <QDebug>

#include "../../utils/utils.h"

#include "imagebutton.h"

client::ImageButton::ImageButton(QPoint position, int height, int width) :
        Widget(position) {
    setHeight(height);
    setWidth(width);
}

void client::ImageButton::paint(QPainter &painter) {
    painter.drawImage(display::getrect(boundsRect()), image);
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
