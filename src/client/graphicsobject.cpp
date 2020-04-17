#include "graphicsobject.h"
#include "mainwindow.h"

client::GraphicsObject::GraphicsObject(const std::shared_ptr<core::Object>& object): object(object) {}

const std::shared_ptr<core::Object>& client::GraphicsObject::getObject() const {
    return object;
}

int client::GraphicsObject::getHeight() const {
    return height;
}

int client::GraphicsObject::getWidth() const {
    return width;
}

void client::GraphicsObject::update(const QPainter& painter, uint64_t timeDeltaMSec) {
    QPainter objectPainter(MainWindow::getInstance());
    objectPainter.setTransform(painter.transform());
    objectPainter.translate(object->getPosition().x(), object->getPosition().y());
    objectPainter.rotate(object->getRotationAngle());
    for (const std::shared_ptr<SpriteController>& spriteController : spriteControllers) {
        spriteController->update(QPainter(), QRect(-width / 2.0, -height / 2.0, width, height), timeDeltaMSec);
    }
}