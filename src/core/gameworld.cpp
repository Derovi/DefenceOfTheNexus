#include <memory>

#include <QDebug>

#include "gameworld.h"
#include "attributes/resource.h"
#include "object.h"

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
    summonObject(column,QPoint(x1,y1));
    summonObject(column,QPoint(x2,y2));
    for(int j=x1+100;j<=x2-100;j+=100)
        summonObject(wall,QPoint(j,y1));
}
