#include "objectgraphicsdescription.h"

int client::ObjectGraphicsDescription::getWidth() const {
    return width;
}

void client::ObjectGraphicsDescription::setWidth(int width) {
    ObjectGraphicsDescription::width = width;
}

int client::ObjectGraphicsDescription::getHeight() const {
    return height;
}

void client::ObjectGraphicsDescription::setHeight(int height) {
    ObjectGraphicsDescription::height = height;
}

const QStringList& client::ObjectGraphicsDescription::getSpriteControllers() const {
    return spriteControllers;
}

void client::ObjectGraphicsDescription::setSpriteControllers(const QStringList& spriteControllers) {
    ObjectGraphicsDescription::spriteControllers = spriteControllers;
}

const QHash<QString, SpriteDescription>& client::ObjectGraphicsDescription::getSpriteNameToResource() const {
    return spriteNameToResource;
}

void client::ObjectGraphicsDescription::setSpriteNameToResource(
        const QHash<QString, SpriteDescription>& spriteNameToResource) {
    ObjectGraphicsDescription::spriteNameToResource = spriteNameToResource;
}
