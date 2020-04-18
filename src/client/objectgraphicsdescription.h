#ifndef OBJECTGRAPHICSDESCRIPTION_H
#define OBJECTGRAPHICSDESCRIPTION_H

#include <QStringList>

#include "spritedescription.h"
#include "spritecontroller.h"

namespace client {

class ObjectGraphicsDescription {
  public:
    int getWidth() const;

    void setWidth(int width);

    int getHeight() const;

    void setHeight(int height);

    const QStringList& getSpriteControllers() const;

    void setSpriteControllers(const QStringList& spriteControllers);

    const QHash<QString, SpriteDescription>& getSpriteDescriptions();

    void setSpriteDescriptions(const QHash<QString, SpriteDescription>& spriteDescriptions);

  private:
    int width;

    int height;

    QStringList spriteControllers;

    QHash<QString, SpriteDescription> spriteDescriptions;
};

}

#endif //OBJECTGRAPHICSDESCRIPTION_H
