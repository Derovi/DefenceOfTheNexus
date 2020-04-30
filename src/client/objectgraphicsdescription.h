#ifndef OBJECTGRAPHICSDESCRIPTION_H
#define OBJECTGRAPHICSDESCRIPTION_H

#include <QStringList>

#include "spritedescription.h"
#include "spritecontroller.h"

namespace client {

class ObjectGraphicsDescription {
  public:
    ObjectGraphicsDescription();

    int getWidth() const;

    void setWidth(int width);

    int getHeight() const;

    void setHeight(int height);

    QStringList& getSpriteControllers();

    void setSpriteControllers(const QStringList& spriteControllers);

    QHash<QString, SpriteDescription>& getSpriteDescriptions();

    void setSpriteDescriptions(const QHash<QString, SpriteDescription>& spriteDescriptions);

  private:
    int width;

    int height;

    QStringList spriteControllers;

    QHash<QString, SpriteDescription> spriteDescriptions;
};

}

#endif //OBJECTGRAPHICSDESCRIPTION_H
