#include <memory>

#include <QDebug>

#include "gameworld.h"
#include "attributes/resource.h"
#include "object.h"

int core::GameWorld::getHeight() const {
    return height;
}

void core::GameWorld::setHeight(int height) {
    GameWorld::height = height;
}

int core::GameWorld::getWidth() const {
    return width;
}

void core::GameWorld::setWidth(int width) {
    GameWorld::width = width;
}

QVector<QPair<core::ResourceType, int>>& core::GameWorld::getResources() {
    return resources;
}

const QVector<QPair<core::ResourceType, int>>& core::GameWorld::getResources() const {
    return resources;
}

void core::GameWorld::setResources(const QVector<QPair<core::ResourceType, int>>& resources) {
    GameWorld::resources = resources;
}

void core::GameWorld::addResources(core::ResourceType type, int amount) {
    auto it = std::find_if(resources.begin(), resources.end(), [type](const auto& resource) {
       return resource.first == type;
    });
    if (it == resources.end()) {
        resources.append(QPair(type, amount));
    } else {
        it->second += amount;
    }
}

QHash<int64_t, std::shared_ptr<core::Object>>& core::GameWorld::getObjects() {
    return objects;
}

void core::GameWorld::setObjects(const QHash<int64_t, std::shared_ptr<core::Object>>& objects) {
    this->objects = objects;
}

core::GameWorld::~GameWorld() {
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
    std::shared_ptr<Object> object = std::shared_ptr<Object>(
            new Object(lastSummonedId, signature.getTypeName(), position,
                       signature.getHitbox(), rotationAngle));
    object->setStrategies(signature.getStrategies());
    for (std::shared_ptr<core::Attribute> attribute : signature.getAttributes()) {
        object->getAttributes().push_back(attribute->clone());
    }
    objects.insert(lastSummonedId, object);
    return object;
}

core::GameWorld::GameWorld() : lastSummonedId(-1) {}
