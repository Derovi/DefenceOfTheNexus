#include <memory>
#include <cmath>

#include <QDebug>
#include <QMatrix>
#include <QPolygonF>

#include "gameworld.h"
#include "attributes/cost.h"
#include "attributes/resource.h"

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

QVector<QPair<core::ResourceType, int>>& core::GameWorld::getTeamResources(uint8_t team) {
    //qDebug() << "get res" << team;
    return resources[team];
}

const QVector<QPair<core::ResourceType, int>>&
core::GameWorld::getTeamResources(uint8_t team) const {
    //qDebug() << "get res c" << team;
    return resources[team];
}

void core::GameWorld::setTeamResources(const QVector<QPair<core::ResourceType, int>>& resources,
                                       uint8_t team) {
    this->resources[team] = resources;
}

void core::GameWorld::addTeamResources(core::ResourceType type, int amount, uint8_t team) {
    auto it = std::find_if(resources[team].begin(), resources[team].end(),
                           [type](const auto& resource) {
                               return resource.first == type;
                           });
    if (it == resources[team].end()) {
        resources[team].append(QPair(type, amount));
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
                              int team,
                              float rotationAngle) {
    ++lastSummonedId;
    qDebug() << "id:" << lastSummonedId << rotationAngle << team << signature.getTypeName();
    std::shared_ptr<Object> object = std::make_shared<Object>(lastSummonedId,
                                                              signature.getTypeName(),
                                                              position,
                                                              signature.getHitbox(),
                                                              rotationAngle,
                                                              team);
    object->setStrategies(signature.getStrategies());
    for (const auto& attribute : signature.getAttributes()) {
        object->getAttributes().push_back(attribute->clone());
    }
    objects.insert(lastSummonedId, object);
    //qDebug() << "summoned!";
    return object;
}

std::shared_ptr<core::Object>
core::GameWorld::summonObjectIfNoObstacles(const server::ObjectSignature& signature,
                                           const QPoint& position, int team, float rotationAngle) {
    ++lastSummonedId;
    std::shared_ptr<Object> object = std::make_shared<Object>(lastSummonedId,
                                                              signature.getTypeName(),
                                                              position,
                                                              signature.getHitbox(),
                                                              rotationAngle,
                                                              team);
    object->setStrategies(signature.getStrategies());
    for (const auto& attribute : signature.getAttributes()) {
        object->getAttributes().push_back(attribute->clone());
    }
    for (const auto& another : objects) {
        if (object->isIntersect(*another)) {
            return nullptr;
        }
    }
    objects.insert(lastSummonedId, object);
    return object;
}

core::GameWorld::GameWorld(): lastSummonedId(-1), width(0), height(0), teamCount(0) {}

void
core::GameWorld::buildWall(QPoint start, QPoint finish,
                           const server::ObjectSignature& wallSignature,
                           const server::ObjectSignature& columnSignature,
                           uint8_t team) {
    const int WALL_WIDTH = 50;
    const int MAX_WALL_LENGTH = 3;
    server::ObjectSignature wall(wallSignature);
    long double dx = finish.x() - start.x();
    long double dy = finish.y() - start.y();
    long double ang;
    if (dx == 0) {
        dx += 0.1;
    }
    ang = atan2(dy, dx);
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
    for (int j = 0;
         j < all;
         j++) {
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
            if (team != 0 && (columnSignature.getAttribute("cost") != nullptr) &&
                !((dynamic_cast<Cost*>(columnSignature.getAttribute("cost").get()))->pay(
                    resources[team]))) {
                break;
            }
            summonObject(columnSignature,
                         QPoint(start.x() + dx * j * 100, start.y() + dy * j * 100), team, ang);
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
            if (team != 0 && (wall.getAttribute("cost") != nullptr) &&
                !((dynamic_cast<Cost*>(wall.getAttribute("cost").get()))->pay(resources[team]))) {
                break;
            }
            summonObject(wall,
                         QPoint(start.x() + dx * j * 100, start.y() + dy * j * 100),
                         team,
                         ang);
        }
        kol++;
    }
}

bool core::GameWorld::isIntersectsWithObjects(const QPolygonF& polygon) const {
    for (const std::shared_ptr<core::Object>& otherObject: getObjects()) {
        if (otherObject->isIntersect(polygon)) {
            return true;
        }
    }
    return false;
}

std::shared_ptr<core::Object>
core::GameWorld::build(const server::ObjectSignature& signature, const QPoint& position,
                       uint8_t team,
                       float rotationAngle) {
    QPolygonF hitbox = signature.getHitbox();
    QMatrix matrix;
    matrix.rotate(rotationAngle);
    matrix.map(hitbox);
    hitbox.translate(position.x(), position.y());
    if (isIntersectsWithObjects(hitbox)) {
        return nullptr;
    }
    if (team > 0 && team < 255 && (signature.getAttribute("cost") != nullptr) &&
        !((dynamic_cast<Cost*>(signature.getAttribute("cost").get()))->pay(resources[team]))) {
        return nullptr;
    }
    qDebug() << "building at" << position << signature.getTypeName();
    return summonObject(signature, position, team, rotationAngle);
}

std::pair<core::Object, bool>
core::GameWorld::checkBuildStatus(const server::ObjectSignature& signature, const QPoint& position,
                                  uint8_t team,
                                  float rotationAngle) const {
    bool ok = true;
    QPolygonF hitbox = signature.getHitbox();
    QMatrix matrix;
    matrix.rotate(rotationAngle);
    matrix.map(hitbox);
    QVector<QPair<core::ResourceType, int>> copyResources = resources[team];
    hitbox.translate(position.x(), position.y());
    if (isIntersectsWithObjects(hitbox)) {
        ok = false;
    }
    if ((signature.getAttribute("cost") != nullptr) &&
        !((dynamic_cast<Cost*>(signature.getAttribute("cost").get()))->pay(copyResources))) {
        ok = false;
    }
    core::Object ans = Object(lastSummonedId,
                              signature.getTypeName(),
                              position,
                              signature.getHitbox(),
                              rotationAngle);
    ans.setStrategies(signature.getStrategies());
    for (const auto& attribute : signature.getAttributes()) {
        ans.getAttributes().push_back(attribute->clone());
    }
    return std::make_pair(ans, ok);
}

std::pair<core::Object, bool>
core::GameWorld::checkBuildStatus(const server::ObjectSignature& signature, const QPoint& position,
                                  float rotationAngle,
                                  QVector<QPair<core::ResourceType, int>>& copyResources) const {
    bool ok = true;
    QPolygonF hitbox = signature.getHitbox();
    QMatrix matrix;
    matrix.rotate(rotationAngle);
    matrix.map(hitbox);
    hitbox.translate(position.x(), position.y());
    if (isIntersectsWithObjects(hitbox)) {
        ok = false;
    }
    if ((signature.getAttribute("cost") != nullptr) &&
        !((dynamic_cast<Cost*>(signature.getAttribute("cost").get()))->pay(copyResources))) {
        ok = false;
    }
    core::Object ans = Object(lastSummonedId,
                              signature.getTypeName(),
                              position,
                              signature.getHitbox(),
                              rotationAngle);
    ans.setStrategies(signature.getStrategies());
    for (const auto& attribute : signature.getAttributes()) {
        ans.getAttributes().push_back(attribute->clone());
    }
    return std::make_pair(ans, ok);
}

QVector<std::pair<core::Object, bool> >
core::GameWorld::checkWallStatus(QPoint start, QPoint finish,
                                 const server::ObjectSignature& wallSignature,
                                 const server::ObjectSignature& columnSignature,
                                 uint8_t team) const {
    QVector<std::pair<core::Object, bool>> ans;
    const int WALL_WIDTH = 50;
    const int MAX_WALL_LENGTH = 3;
    server::ObjectSignature wall(wallSignature);
    long double dx = finish.x() - start.x();
    long double dy = finish.y() - start.y();
    QVector<QPair<core::ResourceType, int>> copyResources = resources[team];
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
    for (int j = 0;
         j < all;
         j++) {
        if (kol == MAX_WALL_LENGTH || j == all - 1) {
            kol = 0;
        }
        if (kol == 0) {
            QPoint firstPoint(start.x() + dx * j * 100,
                              start.y() + dy * j * 100);
            QPoint secondPoint(start.x() + dx * j * 100 + dx * 25,
                               start.y() + dy * j * 100 + dy * 25);
            ans.push_back({checkBuildStatus(columnSignature, firstPoint, ang, copyResources).first,
                           checkBuildStatus(columnSignature, secondPoint, ang,
                                            copyResources).second});
        } else {
            QPoint firstPoint(start.x() + dx * j * 100,
                              start.y() + dy * j * 100);
            QPoint secondPoint(start.x() + dx * j * 100 + dx * 25,
                               start.y() + dy * j * 100 + dy * 25);
            ans.push_back({checkBuildStatus(wall, firstPoint, ang, copyResources).first,
                           checkBuildStatus(wall, secondPoint, ang, copyResources).second});
        }
        kol++;
    }
    return ans;
}

int core::GameWorld::getTeamCount() const {
    return teamCount;
}

void core::GameWorld::setTeamCount(uint8_t teamCount) {
    resources.resize(teamCount);
    this->teamCount = teamCount;
}

core::GameWorld::GameWorld(const core::GameWorld& base) {
    height = base.height;
    width = base.width;
    teamCount = base.teamCount;
    lastSummonedId = base.lastSummonedId;
    resources = base.resources;
    for (auto it = base.objects.begin();
         it != base.objects.end();
         it++) {
        objects[it.key()] = std::make_shared<core::Object>((*it)->getId(), (*it)->getTypeName(),
                                                           (*it)->getPosition(),
                                                           (*it)->getHitbox(),
                                                           (*it)->getRotationAngle(),
                                                           (*it)->getTeam());
        QLinkedList<std::shared_ptr<Attribute>> attributes;
        for (auto attribute : it.value()->getAttributes()) {
            attributes.push_back(attribute->clone());
        }
        objects[it.key()]->setAttributes(attributes);
    }
}

const QVector<core::Event>& core::GameWorld::getGeneratedEvent() const {
    return generatedEvent;
}

bool core::GameWorld::areEnemies(int firstTeam, int secondTeam) {
    return firstTeam != secondTeam;
}

void core::GameWorld::generateEvent(const core::Event& event) {
    generatedEvent.push_back(event);
}

void core::GameWorld::clearEvents() {
    generatedEvent.clear();
}
