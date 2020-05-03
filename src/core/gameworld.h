#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include <memory>
#include <QMap>
#include <QtCore/QHash>

#include "object.h"
#include "attributes/resource.h"
#include "../server/objectsignature.h"

namespace core {

class GameWorld {
  public:
    GameWorld();

    ~GameWorld() = default;

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

    std::shared_ptr<core::Object>
    summonObject(const server::ObjectSignature& signature, const QPoint& position,
                 float rotationAngle = 0);

    void buildWall(QPoint start, QPoint finish, const server::ObjectSignature& wall,
                   const server::ObjectSignature& columnSignature);

    bool isIntersectsWithObjects(const QPolygonF& polygon);

    int getLastSummonedId() const;

    void setLastSummonedId(int lastSummonedId);

  private:

    int height;
    int width;

    int lastSummonedId;

    QVector<core::Resource> resources;
    QHash<int64_t, std::shared_ptr<core::Object>> objects;
};

}

#endif  // GAMEWORLD_H
