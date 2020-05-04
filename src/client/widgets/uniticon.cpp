#include "uniticon.h"

client::UnitIcon::UnitIcon(QPoint position, int width, int height):
        Widget(position), graphicsObject(nullptr) {
    setWidth(width);
    setHeight(height);
}

void client::UnitIcon::paint(QPainter& painter) {
    painter.drawImage(QRect(0, 0, width, height), background);
    if (graphicsObject != nullptr) {
        graphicsObject->drawTo(painter, QRect(0, 0, width, height));
    }
}

const std::shared_ptr<client::GraphicsObject>& client::UnitIcon::getGraphicsObject() const {
    return graphicsObject;
}

void client::UnitIcon::setGraphicsObject(const std::shared_ptr<GraphicsObject>& graphicsObject) {
    UnitIcon::graphicsObject = graphicsObject;
}

const QImage& client::UnitIcon::getBackground() const {
    return background;
}

void client::UnitIcon::setBackground(const QImage& background) {
    UnitIcon::background = background;
}
