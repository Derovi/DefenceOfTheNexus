#include <QDebug>

#include "gamemap.h"
#include "../windowmanager.h"
#include "../../utils/utils.h"

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
    painter.setPen(QPen(QBrush(colors::interface_green),
                        8, Qt::SolidLine,
                        Qt::SquareCap, Qt::MiterJoin));

    for (const std::shared_ptr<core::Object>& object : gameWorld->getObjects().values()) {
        QPolygon polygon;
        for (auto point : object->getHitbox()) {
            polygon.append(toWidgetPoint(
                    QPoint(point.x() + object->getPosition().x(),
                           point.y() + object->getPosition().y())));
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

QPoint client::GameMap::toWidgetPoint(const QPoint& mapPoint) {
    QPoint widgetPoint = mapPoint;
    widgetPoint -= QPoint(displayBounds.x(), displayBounds.y());
    widgetPoint.setX(widgetPoint.x() * width / displayBounds.width());
    widgetPoint.setY(widgetPoint.y() * height / displayBounds.height());
    return widgetPoint;
}

QPoint client::GameMap::toMapPoint(const QPoint& widgetPoint) {
    QPoint mapPoint = widgetPoint;
    mapPoint.setX(widgetPoint.x() * displayBounds.width() / width);
    mapPoint.setY(widgetPoint.y() * displayBounds.height() / height);
    mapPoint += QPoint(displayBounds.x(), displayBounds.y());
    return mapPoint;
}
