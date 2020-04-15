#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include <memory>
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

    const QVector<core::Resource>& getResources() const;

    void setResources(const QVector<core::Resource>& resources);

    QHash<int64_t, std::shared_ptr<core::Object>>& getObjects();

    const QHash<int64_t, std::shared_ptr<core::Object>>& getObjects() const;


    void setObjects(const QHash<int64_t, std::shared_ptr<core::Object>>& objects);

    ~GameWorld();

  private:

    int height;
    int width;

    QVector<core::Resource> resources;
    QHash<int64_t, std::shared_ptr<core::Object>> objects;
};

}

#endif  // GAMEWORLD_H
