#include <QDebug>

#include "../utils/factory.h"

#include "graphicsobject.h"
#include "mainwindow.h"
#include "spritecontrollers/unitspritecontroller.h"

client::GraphicsObject::GraphicsObject(const std::shared_ptr<core::Object>& object):
        object(object), width(object->getHitbox().boundingRect().width()), height(
        object->getHitbox().boundingRect().height()) {
    //! TODO fix this costyl
//    spriteControllers = {utils::Factory::createSpriteController(UnitSpriteController::name, object)};
    for (const QString& spriteControllerName : utils::Factory::getObjectGraphicsDescription(
            object->getTypeName())->getSpriteControllers()) {
        spriteControllers.push_back(
                utils::Factory::createSpriteController(spriteControllerName, object));
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
    objectPainter.rotate(object->getRotationAngle());
    for (const std::shared_ptr<SpriteController>& spriteController : spriteControllers) {
        int textureHeight = height;
        int textureWidth = width;
        auto objectGraphicsDescription = utils::Factory::getObjectGraphicsDescription(
                object->getTypeName());
        if (objectGraphicsDescription != std::nullopt &&
            objectGraphicsDescription.value().getWidth() > 0 &&
            objectGraphicsDescription.value().getHeight() > 0) {
            textureWidth = objectGraphicsDescription.value().getWidth();
            textureHeight = objectGraphicsDescription.value().getHeight();
        }
        spriteController->update(objectPainter,
                                 QRect(-textureWidth / 2.0, -textureHeight / 2.0, textureWidth,
                                       textureHeight),
                                 timeDeltaMSec);
    }
}
