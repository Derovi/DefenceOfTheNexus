#include "uniticon.h"

client::UnitIcon::UnitIcon(QPoint position, int width, int height):
        Widget(position), graphicsObject(nullptr) {
    setWidth(width);
    setHeight(height);
}

void client::UnitIcon::paint(QPainter& painter) {
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
