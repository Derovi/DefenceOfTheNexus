#include <memory>
#include <cmath>

#include <QDebug>
#include <QMatrix>
#include <QPolygonF>

#include "gameworld.h"
#include "attributes/cost.h"
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

std::shared_ptr<core::Object> core::GameWorld::objectAt(QPointF point) {
    for (const auto& object : objects) {
        QPointF mapped(point.x() - object->getPosition().x(),
                       point.y() - object->getPosition().y());
        if (object->getHitbox().containsPoint(mapped, Qt::OddEvenFill)) {
            return object;
        }
    }
    return nullptr;
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

void
core::GameWorld::buildWall(QPoint start, QPoint finish,
                           const server::ObjectSignature& wallSignature,
                           const server::ObjectSignature& columnSignature) {
    const int WALL_WIDTH = 50;
    const int MAX_WALL_LENGTH = 3;
    server::ObjectSignature wall(wallSignature);
    long double dx = finish.x() - start.x();
    long double dy = finish.y() - start.y();
    long double ang;
    if (dx == 0) {
        ang = 0;
    } else { ang = atan2(dy, dx); }
    long double dz = sqrt(dx * dx + dy * dy);
    int all = dz / 100;
    dx /= dz;
    dy /= dz;
    int kol = 0;
    ang *= 180 / M_PI;
    QVector<QPoint> vec;
    vec.push_back(QPoint(-50, -WALL_WIDTH / 2));
    vec.push_back(QPoint(-50, WALL_WIDTH / 2));
    vec.push_back(QPoint(50, WALL_WIDTH / 2));
    vec.push_back(QPoint(50, -WALL_WIDTH / 2));
    wall.setHitbox(QPolygonF(vec));
    for (int j = 0; j < all; j++) {
        if (kol == MAX_WALL_LENGTH || j == all - 1) {
            kol = 0;
        }
        if (kol == 0) {
            QPolygonF hitbox = columnSignature.getHitbox();
            QMatrix matrix;
            matrix.rotate(ang);
            matrix.map(hitbox);
            hitbox.translate(start.x() + dx * j * 100 + dx * 25,
                             start.y() + dy * j * 100 + dy * 25);
            if (isIntersectsWithObjects(hitbox)) {
                kol++;
                continue;
            }
            //!TODO fix
            /*if ((columnSignature.getAttribute("cost") != nullptr) &&
                !((dynamic_cast<Cost*>(columnSignature.getAttribute("cost").get()))->pay(
                        resources))) {
                break;
            }*/
            summonObject(columnSignature,
                         QPoint(start.x() + dx * j * 100, start.y() + dy * j * 100), ang);
        } else {
            QPolygonF hitbox = wall.getHitbox();
            QMatrix matrix;
            matrix.rotate(ang);
            matrix.map(hitbox);
            hitbox.translate(start.x() + dx * j * 100 + dx * 25,
                             start.y() + dy * j * 100 + dy * 25);
            if (isIntersectsWithObjects(hitbox)) {
                kol++;
                continue;
            }
            //!TODO fix
            /*
            if ((wall.getAttribute("cost") != nullptr) &&
                !((dynamic_cast<Cost*>(wall.getAttribute("cost").get()))->pay(resources))) {
                break;
            }*/
            summonObject(wall, QPoint(start.x() + dx * j * 100, start.y() + dy * j * 100), ang);
        }
        kol++;
    }
}

bool core::GameWorld::isIntersectsWithObjects(const QPolygonF& polygon) {
    for (const std::shared_ptr<core::Object>& otherObject: getObjects()) {
        if (otherObject->isIntersect(polygon)) {
            return true;
        }
    }
    return false;
}
