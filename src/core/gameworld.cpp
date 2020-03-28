#include "gameworld.h"
#include "resource.h"
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

QVector<core::Resource>& core::GameWorld::getResources() {
    return resources;
}

void core::GameWorld::setResources(const QVector<core::Resource>& resources) {
    GameWorld::resources = resources;
}

QHash<int64_t, core::Object*>& core::GameWorld::getObjects() {
    return objects;
}

void core::GameWorld::setObjects(const QHash<int64_t, core::Object*> objects) {
    GameWorld::objects = objects;
}

core::GameWorld::~GameWorld() {
    for (core::Object* object : objects.values()) {
        delete object;
    }
}
