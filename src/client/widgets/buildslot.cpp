#include <QDebug>

#include "buildslot.h"
#include "../screens/gamescreen.h"

client::BuildSlot::BuildSlot(QPoint position, int height, int width):
        Widget(position), hoverHeight(height), hoverWidth(width) {
    setHeight(height);
    setWidth(width);
}

void client::BuildSlot::paint(QPainter& painter) {
    if (objectType.length() == 0) {
        return;
    }
    if (is_hovered && !hoverImage.isNull()) {
        painter.drawImage(QRect(boundsRect().center().x() - hoverWidth / 2,
                                boundsRect().center().y() - hoverHeight / 2,
                                hoverWidth,
                                hoverHeight),
                          hoverImage);
    } else {
        painter.drawImage(boundsRect(), image);
    }
}

void client::BuildSlot::setImage(QImage image) {
    this->image = image;
}

QImage client::BuildSlot::getImage() {
    return image;
}

const QImage& client::BuildSlot::getHoverImage() const {
    return hoverImage;
}

void client::BuildSlot::setHoverImage(const QImage& hoverImage) {
    BuildSlot::hoverImage = hoverImage;
}

int client::BuildSlot::getHoverHeight() const {
    return hoverHeight;
}

void client::BuildSlot::setHoverHeight(int hoverHeight) {
    BuildSlot::hoverHeight = hoverHeight;
}

int client::BuildSlot::getHoverWidth() const {
    return hoverWidth;
}

void client::BuildSlot::setHoverWidth(int hoverWidth) {
    BuildSlot::hoverWidth = hoverWidth;
}

const QString& client::BuildSlot::getObjectType() const {
    return objectType;
}

void client::BuildSlot::setObjectType(const QString& objectType) {
    BuildSlot::objectType = objectType;
}

void client::BuildSlot::clicked(QPoint point, bool leftButton) {
    if (objectType.length() == 0) {
        return;
    }
    dynamic_cast<GameScreen*>(getParent())->getGameMap()->buildCommand(objectType);
}
