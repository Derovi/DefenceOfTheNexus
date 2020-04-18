#include <QDebug>

#include "../utils/colors.h"
#include "graphicsobject.h"
#include "mainwindow.h"
#include "spritecontrollers/uni1spritecontroller.h"

client::GraphicsObject::GraphicsObject(const std::shared_ptr<core::Object>& object):
        object(object), width(object->getHitbox().boundingRect().width()), height(
                              object->getHitbox().boundingRect().height()) {
    qDebug() << "new object!";
    spriteControllers.push_back(
            std::shared_ptr<SpriteController>(new Uni1SpriteController(object)));
}

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
    objectPainter.setPen(QPen(QBrush(colors::border),
                              8, Qt::SolidLine,
                              Qt::SquareCap, Qt::MiterJoin));
    //objectPainter.translate(2000, 2000);
    //objectPainter.drawRect(QRect(0,0,500,500));
    qDebug() << "id" << object->getId() << object->getPosition().x() << object->getPosition().y();
    objectPainter.translate(object->getPosition().x(), object->getPosition().y());
    //objectPainter.rotate(object->getRotationAngle());
    qDebug() << "w" << width << height;
    for (const std::shared_ptr<SpriteController>& spriteController : spriteControllers) {
        spriteController->update(objectPainter, QRect(-width / 2.0, -height / 2.0, width, height),
                                 timeDeltaMSec);
    }
}
