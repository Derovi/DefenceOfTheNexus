#include "spritedescription.h"

const QString& SpriteDescription::getResourceName() const {
    return resourceName;
}

void SpriteDescription::setResourceName(const QString& resourceName) {
    SpriteDescription::resourceName = resourceName;
}

int SpriteDescription::getWidth() const {
    return width;
}

void SpriteDescription::setWidth(int width) {
    SpriteDescription::width = width;
}

int SpriteDescription::getHeight() const {
    return height;
}

void SpriteDescription::setHeight(int height) {
    SpriteDescription::height = height;
}

SpriteDescription::SpriteDescription(const QString& resourceName, int width, int height):
        resourceName(resourceName), width(width), height(height) {}
