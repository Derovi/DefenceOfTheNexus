#include <memory>
#include <cmath>

#include <QDebug>

#include "gameworld.h"
#include "attributes/resource.h"
#include "object.h"
#include "../server/performers/movingperformer.h"

int core::GameWorld::getHeight() const {
    return height;
}

void core::GameWorld::setHeight(int height) {
    this->height = height;
}

int core::GameWorld::getWidth() const {
    return width;
}

void core::GameWorld::setWidth(int width) {
    this->width = width;
}

QVector<core::Resource>& core::GameWorld::getResources() {
    return resources;
}

const QVector<core::Resource>& core::GameWorld::getResources() const {
    return resources;
}

void core::GameWorld::setResources(const QVector<core::Resource>& resources) {
    this->resources = resources;
}

QHash<int64_t, std::shared_ptr<core::Object>>& core::GameWorld::getObjects() {
    return objects;
}

void core::GameWorld::setObjects(const QHash<int64_t, std::shared_ptr<core::Object>>& objects) {
    this->objects = objects;
}

const QHash<int64_t, std::shared_ptr<core::Object>>& core::GameWorld::getObjects() const {
    return objects;
}

int core::GameWorld::getLastSummonedId() const {
    return lastSummonedId;
}

void core::GameWorld::setLastSummonedId(int lastSummonedId) {
    GameWorld::lastSummonedId = lastSummonedId;
}

std::shared_ptr<core::Object>
core::GameWorld::summonObject(const server::ObjectSignature& signature, const QPoint& position,
                              float rotationAngle) {
    ++lastSummonedId;
    std::shared_ptr<Object> object = std::make_shared<Object>(lastSummonedId,
                                                              signature.getTypeName(),
                                                              position,
                                                              signature.getHitbox(),
                                                              rotationAngle);
    object->setStrategies(signature.getStrategies());
    for (const auto& attribute : signature.getAttributes()) {
        object->getAttributes().push_back(attribute->clone());
    }
    objects.insert(lastSummonedId, object);
    return object;
}


core::GameWorld::GameWorld(): lastSummonedId(-1), width(0), height(0) {}

void core::GameWorld::buildWall(int x1, int y1, int x2, int y2, const server::ObjectSignature& wall,
                                const server::ObjectSignature& column) {
    long double dx = x2 - x1;
    long double dy = y2 - y1;
    long double ang;
    if (dx == 0) {
        ang = 0;
    } else { ang = atan2(dy, dx); }
    long double dz = sqrt(dx * dx + dy * dy);
    int all = dz / 100;
    dx /= dz;
    dy /= dz;
    int kol = 0;
    int MAX_WALL_LENGTH = 10;
    for (int j = 0;
         j < all;
         j++) {
        if (kol == MAX_WALL_LENGTH || j == all - 1) {
            kol = 0;
        }

        if (kol == 0) {
          //  if(!server::moving_performer::isIntersect(make_shared))
            summonObject(column, QPoint(x1 + dx * j*100, y1 + dy * j*100), ang);
        } else {
            summonObject(wall, QPoint(x1 + dx * j*100, y1 + dy * j*100), ang);
        }
        kol++;
    }
}
