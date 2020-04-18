#ifndef OBJECTGRAPHICSDESCRIPTION_H
#define OBJECTGRAPHICSDESCRIPTION_H

#include <QStringList>

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

    const QHash<QString, QString>& getSpriteNameToResource() const;

    void setSpriteNameToResource(const QHash<QString, QString>& spriteNameToResource);

  private:
    int width;

    int height;

    QStringList spriteControllers;

    QHash<QString, QString> spriteNameToResource;
};

}

#endif //OBJECTGRAPHICSDESCRIPTION_H
