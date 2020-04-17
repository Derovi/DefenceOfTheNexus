#include <QDebug>

#include "gamemap.h"
#include "../../utils/colors.h"

client::GameMap::GameMap(QPoint position, int height, int width):
        Widget(position) {
    setHeight(height);
    setWidth(width);
    setDisplayBounds(QRect(0, 0, width, height));
}

void client::GameMap::setHeight(int height) {
    this->height = height;
}

void client::GameMap::setWidth(int width) {
    this->width = width;
}

const QRect& client::GameMap::getDisplayBounds() const {
    return displayBounds;
}

void client::GameMap::setDisplayBounds(const QRect& displayBounds) {
    GameMap::displayBounds = displayBounds;
}

void client::GameMap::paint(QPainter& painter) {
    //painter.translate(displayBounds.x(), displayBounds.y());
    painter.setTransform(getTransformToWidget(), true);
    painter.setPen(QPen(QBrush(colors::border),
                        8, Qt::SolidLine,
                        Qt::SquareCap, Qt::MiterJoin));

    for (const std::shared_ptr<core::Object>& object : gameWorld->getObjects().values()) {
        QPolygon polygon;
        for (auto point : object->getHitbox()) {
            polygon.append(QPoint(point.x() + object->getPosition().x(),
                           point.y() + object->getPosition().y()));
        }
        painter.drawPolygon(polygon);
    }
}

const std::shared_ptr<core::GameWorld>& client::GameMap::getGameWorld() const {
    return gameWorld;
}

void client::GameMap::setGameWorld(const std::shared_ptr<core::GameWorld>& gameWorld) {
    GameMap::gameWorld = gameWorld;
}

QTransform client::GameMap::getTransformToWidget() const {
    return QTransform(1, 0, 0, 1, -displayBounds.x(), -displayBounds.y()) *
           QTransform(width / displayBounds.width(), 0, 0, height / displayBounds.height(), 0, 0);
}

QTransform client::GameMap::getTransformToMap() const {
    return getTransformToWidget().inverted();
}
