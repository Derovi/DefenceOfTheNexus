#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include <QMap>
#include <QtCore/QHash>

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

    QHash<int64_t, core::Object*>& getObjects();

    void setObjects(const QHash<int64_t, core::Object*>& objects);

    ~GameWorld();

  private:

    const QMap<int64_t, core::Object*> getObjects() const;

    void setObjects(const QMap<int64_t, core::Object*> objects);

    int height;
    int width;

    QVector<core::Resource> resources;
    QHash<int64_t, core::Object*> objects;
};

}

#endif  // GAMEWORLD_H
