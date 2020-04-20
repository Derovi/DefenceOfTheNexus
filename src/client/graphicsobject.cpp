#include <QDebug>

#include "../utils/colors.h"
#include "../utils/factory.h"

#include "graphicsobject.h"
#include "mainwindow.h"
#include "spritecontrollers/unitspritecontroller.h"

client::GraphicsObject::GraphicsObject(const std::shared_ptr<core::Object>& object):
        object(object), width(object->getHitbox().boundingRect().width()), height(
        object->getHitbox().boundingRect().height()) {
    for (QString spriteControllerName : utils::Factory::getObjectGraphicsDescription(
            object->getTypeName())->getSpriteControllers()) {
        spriteControllers.push_back(utils::Factory::createSpriteController(spriteControllerName, object));
    }
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

void client::GraphicsObject::update(const QTransform& painterTransform, uint64_t timeDeltaMSec) {
    QPainter objectPainter(MainWindow::getInstance());
    objectPainter.setTransform(painterTransform);
    objectPainter.translate(object->getPosition().x(), object->getPosition().y());
    for (const std::shared_ptr<SpriteController>& spriteController : spriteControllers) {
        spriteController->update(objectPainter, QRect(-width / 2.0, -height / 2.0, width, height),
                                 timeDeltaMSec);
    }
}