#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include <QMap>
#include "object.h"
#include "resource.h"

namespace core {

class GameWorld {
  public:
    int getHeight() const;

    void setHeight(int height);

    int getWidth() const;

    void setWidth(int width);

    QVector<core::Resource>& getResources();

    void setResources(const QVector<core::Resource>& resources);

    QMap<int64_t, core::Object*>& getObjects();

    void setObjects(const QMap<int64_t, core::Object*> objects);

  public:

  private:

    int height;
    int width;

    QVector<core::Resource> resources;
    QMap<int64_t, core::Object*> objects;
};

}

#endif  // GAMEWORLD_H
