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

    QVector<QPair<core::ResourceType, int>>& getTeamResources(uint8_t team);

    const QVector<QPair<core::ResourceType, int>>& getTeamResources(uint8_t team) const;

    void setTeamResources(const QVector<QPair<core::ResourceType, int>>& resources, uint8_t team);

    void addTeamResources(core::ResourceType type, int amount, uint8_t team);

    QHash<int64_t, std::shared_ptr<core::Object>>& getObjects();

    const QHash<int64_t, std::shared_ptr<core::Object>>& getObjects() const;

    void setObjects(const QHash<int64_t, std::shared_ptr<core::Object>>& objects);

    std::shared_ptr<core::Object> objectAt(QPointF point);

    std::shared_ptr<core::Object>
    summonObject(const server::ObjectSignature& signature, const QPoint& position,
                 float rotationAngle = 0);

    void buildWall(QPoint start, QPoint finish, const server::ObjectSignature& wall,
                   const server::ObjectSignature& columnSignature, uint8_t team = 255);

    bool isIntersectsWithObjects(const QPolygonF& polygon) const;

    bool areEnemies(int firstTeam, int secondTeam);

    int getLastSummonedId() const;

    void setLastSummonedId(int lastSummonedId);

    int getTeamCount() const;

    void setTeamCount(uint8_t teamCount);

    std::shared_ptr<core::Object>
    build(const server::ObjectSignature& signature, const QPoint& position, uint8_t team,
          float rotationAngle = 0);

    std::pair<core::Object, bool>
    checkBuildStatus(const server::ObjectSignature& signature, const QPoint& position,
                     uint8_t team,
                     float rotationAngle = 0) const;

    std::pair<core::Object, bool>
    checkBuildStatus(const server::ObjectSignature& signature,
                     const QPoint& position,
                     float rotationAngle,
                     QVector<QPair<core::ResourceType, int>>& copyResources) const;

    QVector<std::pair<core::Object, bool>>
    checkWallStatus(QPoint start, QPoint finish, const server::ObjectSignature& wall,
                    const server::ObjectSignature& columnSignature,
                    uint8_t team) const;

    GameWorld(const core::GameWorld &base);


  private:
    QVector<QVector<QPair<core::ResourceType, int>>> resources;
    QHash<int64_t, std::shared_ptr<core::Object>> objects;

    int height;
    int width;
    //!TODO add to serialization
    uint8_t teamCount;

    int lastSummonedId;
};

}

#endif  // GAMEWORLD_H
