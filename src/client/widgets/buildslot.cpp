#include <QDebug>

#include "buildslot.h"

#include "../screens/gamescreen.h"
#include "../../utils/factory.h"

client::BuildSlot::BuildSlot(QPoint position, int height, int width):
        Widget(position), hoverHeight(height), hoverWidth(width) {
    setHeight(height);
    setWidth(width);
}

void client::BuildSlot::paint(QPainter& painter) {
    if (objectType.isEmpty()) {
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
    auto graphicsDescription = utils::Factory::getObjectGraphicsDescription(objectType);
    if (!graphicsDescription) {
        return;
    }
    if (graphicsDescription->getSpriteDescriptions().empty()) {
        return;
    }
    auto spriteDescription = graphicsDescription->getSpriteDescriptions().begin().value();
    if (spriteResource != spriteDescription.getResourceName()) {
        spriteResource = spriteDescription.getResourceName();
        iconSprite = Sprite(spriteDescription);
    }
    QMatrix matrix;
    matrix.translate(0.15 * boundsRect().width(), 0.15 * boundsRect().height());
    matrix.scale(0.7, 0.7);
    iconSprite.draw(painter, matrix.mapRect(boundsRect()));
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
    qDebug() << "clicked input!";
    if (objectType.length() == 0) {
        return;
    }
    dynamic_cast<GameScreen*>(getParent()->getParent())->getGameMap()->getMapInput()->setObjectType(getObjectType());
}
