#include "objectgraphicsdescription.h"

client::ObjectGraphicsDescription::ObjectGraphicsDescription(): height(0), width(0) {}

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

QStringList& client::ObjectGraphicsDescription::getSpriteControllers() {
    return spriteControllers;
}

void client::ObjectGraphicsDescription::setSpriteControllers(const QStringList& spriteControllers) {
    ObjectGraphicsDescription::spriteControllers = spriteControllers;
}


QHash<QString, SpriteDescription>&
client::ObjectGraphicsDescription::getSpriteDescriptions() {
    return spriteDescriptions;
}

void
client::ObjectGraphicsDescription::setSpriteDescriptions(
        const QHash<QString, SpriteDescription>& spriteDescriptions) {
    ObjectGraphicsDescription::spriteDescriptions = spriteDescriptions;
}
