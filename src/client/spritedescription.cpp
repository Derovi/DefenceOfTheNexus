
#include <QtCore/QString>
#include "spritedescription.h"

const QString& SpriteDescription::getResourceName() const {
    return resourceName;
}

void SpriteDescription::setResourceName(const QString& resourceName) {
    SpriteDescription::resourceName = resourceName;
}

int SpriteDescription::getRows() const {
    return rows;
}

void SpriteDescription::setRows(int rows) {
    SpriteDescription::rows = rows;
}

int SpriteDescription::getColumns() const {
    return columns;
}

void SpriteDescription::setColumns(int columns) {
    SpriteDescription::columns = columns;
}

SpriteDescription::SpriteDescription(const QString& resourceName, int rows, int columns):
        resourceName(resourceName), rows(rows), columns(columns) {}

