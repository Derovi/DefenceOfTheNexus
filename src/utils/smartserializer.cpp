#include "smartserializer.h"
#include "factory.h"
#include "../core/attributes/bullet.h"

utils::SmartSerializer::SmartSerializer(bool prettyPrinting) {
    utils::SmartSerializer::prettyPrinting = prettyPrinting;
}

QJsonObject utils::SmartSerializer::objectPartSerializer(
    const std::shared_ptr<core::Object>& beforeChanges,
    const std::shared_ptr<core::Object>& afterChanges,
    const utils::KeyManager& keyManager) {
    QJsonObject result;
    const double EPS = 1e-4;
    if (std::abs(beforeChanges->getRotationAngle() - afterChanges->getRotationAngle()) > EPS) {
        result.insert("rotationAngle",
                      static_cast<int>(afterChanges->getRotationAngle() * 100) / 100.0);
    }
    if (std::abs(beforeChanges->getSightAngle() - afterChanges->getSightAngle()) > EPS) {
        result.insert("sightAngle",
                      static_cast<int>(afterChanges->getSightAngle() * 100) / 100.0);
    }
    if (beforeChanges->getTypeName() != afterChanges->getTypeName()) {
        result.insert("typeName", afterChanges->getTypeName());
    }
    if (beforeChanges->getPosition() != afterChanges->getPosition()) {
        QJsonObject position;
        position.insert("x", afterChanges->getPosition().x());
        position.insert("y", afterChanges->getPosition().y());
        result.insert("position", position);
    }
    if (beforeChanges->getStrategies() != afterChanges->getStrategies()) {
        QJsonArray strategies;
        for (const auto& strategy : afterChanges->getStrategies()) {
            strategies.push_back(strategy);
        }
        result["strategies"] = strategies;
    }
    QJsonObject attributes;
    for (const auto& j:afterChanges->getAttributes()) {
        for (const auto& k: beforeChanges->getAttributes()) {
            if (j->getAttributeName() == k->getAttributeName()) {
                QJsonObject serialized = utils::Factory::getPartSerializer(j->getAttributeName())(j,
                                                                                                  k,
                                                                                                  keyManager);
                if (serialized.size() != 0) {
                    attributes.insert(j->getAttributeName(), serialized);
                }
            }
        }
    }
    if (attributes.size() != 0) {
        result.insert("attributes", attributes);
    }
    if (beforeChanges->getHitbox() != afterChanges->getHitbox()) {
        QPolygonF hitbox = afterChanges->getHitbox();
        QJsonArray xArray, yArray;
        QJsonObject position;
        for (const auto& i : hitbox) {
            xArray.push_back(i.x());
            yArray.push_back(i.y());
        }
        position.insert("x", xArray);
        position.insert("y", yArray);
        result.insert("hitbox", position);
    }
    return jsonToHashed(result, keyManager);
}

void
utils::SmartSerializer::resourcePartDeserializer(const std::shared_ptr<core::Attribute>& resource,
                                                 const QJsonObject& changes,
                                                 const utils::KeyManager& keyManager) {
    auto deserializer = utils::Factory::getDeserializer("resource");
    std::shared_ptr<core::Attribute> ptr = deserializer(hashedToJson(changes, keyManager)).value();
    *dynamic_cast<core::Resource*>(resource.get()) = *dynamic_cast<core::Resource*>(ptr.get());
}

void
utils::SmartSerializer::damagingPartDeserializer(const std::shared_ptr<core::Attribute>& resource,
                                                 const QJsonObject& changes,
                                                 const utils::KeyManager& keyManager) {
    auto deserializer = utils::Factory::getDeserializer("damaging");
    std::shared_ptr<core::Attribute> ptr = deserializer(hashedToJson(changes, keyManager)).value();
    *dynamic_cast<core::Damaging*>(resource.get()) = *dynamic_cast<core::Damaging*>(ptr.get());
}

void
utils::SmartSerializer::damageablePartDeserializer(const std::shared_ptr<core::Attribute>& resource,
                                                   const QJsonObject& changes,
                                                   const utils::KeyManager& keyManager) {
    auto deserializer = utils::Factory::getDeserializer("damageable");
    std::shared_ptr<core::Attribute> ptr = deserializer(hashedToJson(changes, keyManager)).value();
    *dynamic_cast<core::Damageable*>(resource.get()) = *dynamic_cast<core::Damageable*>(ptr.get());
}

void
utils::SmartSerializer::movingPartDeserializer(const std::shared_ptr<core::Attribute>& resource,
                                               const QJsonObject& changes,
                                               const utils::KeyManager& keyManager) {
    auto deserializer = utils::Factory::getDeserializer("moving");
    std::shared_ptr<core::Attribute> ptr = deserializer(hashedToJson(changes, keyManager)).value();
    *dynamic_cast<core::Moving*>(resource.get()) = *dynamic_cast<core::Moving*>(ptr.get());
}

void
utils::SmartSerializer::miningPartDeserializer(const std::shared_ptr<core::Attribute>& resource,
                                               const QJsonObject& changes,
                                               const utils::KeyManager& keyManager) {
    auto deserializer = utils::Factory::getDeserializer("mining");
    std::shared_ptr<core::Attribute> ptr = deserializer(hashedToJson(changes, keyManager)).value();
    *dynamic_cast<core::Mining*>(resource.get()) = *dynamic_cast<core::Mining*>(ptr.get());
}

void utils::SmartSerializer::bulletPartDeserializer(const std::shared_ptr<core::Attribute>& resource,
                                                    const QJsonObject& changes,
                                                    const utils::KeyManager& keyManager) {
    auto deserializer = utils::Factory::getDeserializer("bullet");
    std::shared_ptr<core::Attribute> ptr = deserializer(hashedToJson(changes, keyManager)).value();
    *dynamic_cast<core::Bullet*>(resource.get()) = *dynamic_cast<core::Bullet*>(ptr.get());
}

void utils::SmartSerializer::wallPartDeserializer(const std::shared_ptr<core::Attribute>& resource,
                                                  const QJsonObject& changes,
                                                  const utils::KeyManager& keyManager) {
    auto deserializer = utils::Factory::getDeserializer("wall");
    std::shared_ptr<core::Attribute> ptr = deserializer(hashedToJson(changes, keyManager)).value();
    *dynamic_cast<core::Wall*>(resource.get()) = *dynamic_cast<core::Wall*>(ptr.get());
}

void utils::SmartSerializer::costPartDeserializer(const std::shared_ptr<core::Attribute>& resource,
                                                  const QJsonObject& changes,
                                                  const utils::KeyManager& keyManager) {
    auto deserializer = utils::Factory::getDeserializer("cost");
    std::shared_ptr<core::Attribute> ptr = deserializer(hashedToJson(changes, keyManager)).value();
    *dynamic_cast<core::Cost*>(resource.get()) = *dynamic_cast<core::Cost*>(ptr.get());

}

void
utils::SmartSerializer::builderPartDeserializer(const std::shared_ptr<core::Attribute>& resource,
                                                const QJsonObject& changes,
                                                const utils::KeyManager& keyManager) {
    auto deserializer = utils::Factory::getDeserializer("builder");
    std::shared_ptr<core::Attribute> ptr = deserializer(hashedToJson(changes, keyManager)).value();
    *dynamic_cast<core::Builder*>(resource.get()) = *dynamic_cast<core::Builder*>(ptr.get());
}

QJsonObject utils::SmartSerializer::resourcePartSerializer(
    const std::shared_ptr<core::Attribute>& beforeChanges,
    const std::shared_ptr<core::Attribute>& afterChanges,
    const utils::KeyManager& keyManager) {
    if ((*dynamic_cast<core::Resource*>(beforeChanges.get())) ==
        (*dynamic_cast<core::Resource*>(afterChanges.get()))) {
        return QJsonObject();
    }
    auto seriazlier = utils::Factory::getSerializer("resource");
    return jsonToHashed(seriazlier(afterChanges).value(), keyManager);
}

QJsonObject utils::SmartSerializer::damagingPartSerializer(
    const std::shared_ptr<core::Attribute>& beforeChanges,
    const std::shared_ptr<core::Attribute>& afterChanges, const utils::KeyManager& keyManager) {
    if ((*dynamic_cast<core::Damaging*>(beforeChanges.get())) ==
        (*dynamic_cast<core::Damaging*>(afterChanges.get()))) {
        return QJsonObject();
    }
    auto seriazlier = utils::Factory::getSerializer("damaging");
    return jsonToHashed(seriazlier(afterChanges).value(), keyManager);
}

QJsonObject utils::SmartSerializer::damageablePartSerializer(
    const std::shared_ptr<core::Attribute>& beforeChanges,
    const std::shared_ptr<core::Attribute>& afterChanges, const utils::KeyManager& keyManager) {
    if ((*dynamic_cast<core::Damageable*>(beforeChanges.get())) ==
        (*dynamic_cast<core::Damageable*>(afterChanges.get()))) {
        return QJsonObject();
    }
    auto seriazlier = utils::Factory::getSerializer("damageable");
    return jsonToHashed(seriazlier(afterChanges).value(), keyManager);
}

QJsonObject
utils::SmartSerializer::movingPartSerializer(const std::shared_ptr<core::Attribute>& beforeChanges,
                                             const std::shared_ptr<core::Attribute>& afterChanges,
                                             const utils::KeyManager& keyManager) {
    if ((*dynamic_cast<core::Moving*>(beforeChanges.get())) ==
        (*dynamic_cast<core::Moving*>(afterChanges.get()))) {
        return QJsonObject();
    }
    auto seriazlier = utils::Factory::getSerializer("moving");
    return jsonToHashed(seriazlier(afterChanges).value(), keyManager);
}

QJsonObject
utils::SmartSerializer::miningPartSerializer(const std::shared_ptr<core::Attribute>& beforeChanges,
                                             const std::shared_ptr<core::Attribute>& afterChanges,
                                             const utils::KeyManager& keyManager) {
    if ((*dynamic_cast<core::Mining*>(beforeChanges.get())) ==
        (*dynamic_cast<core::Mining*>(afterChanges.get()))) {
        return QJsonObject();
    }
    auto seriazlier = utils::Factory::getSerializer("mining");
    return jsonToHashed(seriazlier(afterChanges).value(), keyManager);
}

QJsonObject utils::SmartSerializer::bulletPartSerializer(const std::shared_ptr<core::Attribute>& beforeChanges,
                                                         const std::shared_ptr<core::Attribute>& afterChanges,
                                                         const utils::KeyManager& keyManager) {
    if ((*dynamic_cast<core::Bullet*>(beforeChanges.get()))
        == (*dynamic_cast<core::Bullet*>(afterChanges.get()))) {
        return QJsonObject();
    }
    auto seriazlier = utils::Factory::getSerializer("bullet");
    return jsonToHashed(seriazlier(afterChanges).value(), keyManager);
}

QJsonObject
utils::SmartSerializer::wallPartSerializer(const std::shared_ptr<core::Attribute>& beforeChanges,
                                           const std::shared_ptr<core::Attribute>& afterChanges,
                                           const utils::KeyManager& keyManager) {
    if ((*dynamic_cast<core::Wall*>(beforeChanges.get())) ==
        (*dynamic_cast<core::Wall*>(afterChanges.get()))) {
        return QJsonObject();
    }
    auto seriazlier = utils::Factory::getSerializer("wall");
    return jsonToHashed(seriazlier(afterChanges).value(), keyManager);
}

QJsonObject
utils::SmartSerializer::costPartSerializer(const std::shared_ptr<core::Attribute>& beforeChanges,
                                           const std::shared_ptr<core::Attribute>& afterChanges,
                                           const utils::KeyManager& keyManager) {
    if ((*dynamic_cast<core::Cost*>(beforeChanges.get())) ==
        (*dynamic_cast<core::Cost*>(afterChanges.get()))) {
        return QJsonObject();
    }
    auto seriazlier = utils::Factory::getSerializer("cost");
    return jsonToHashed(seriazlier(afterChanges).value(), keyManager);
}

QJsonObject
utils::SmartSerializer::builderPartSerializer(const std::shared_ptr<core::Attribute>& beforeChanges,
                                              const std::shared_ptr<core::Attribute>& afterChanges,
                                              const utils::KeyManager& keyManager) {
    if ((*dynamic_cast<core::Builder*>(beforeChanges.get())) ==
        (*dynamic_cast<core::Builder*>(afterChanges.get()))) {
        return QJsonObject();
    }
    auto seriazlier = utils::Factory::getSerializer("builder");
    return jsonToHashed(seriazlier(afterChanges).value(), keyManager);
}

QJsonObject utils::SmartSerializer::gamePartWorldSerializer(
    const std::shared_ptr<const core::GameWorld>& beforeChanges,
    const std::shared_ptr<const core::GameWorld>& afterChanges,
    const utils::KeyManager& keyManager) {
    QJsonObject result;
    if (beforeChanges->getWidth() != afterChanges->getWidth()) {
        result.insert("width", afterChanges->getWidth());
    }
    if (beforeChanges->getHeight() != afterChanges->getHeight()) {
        result.insert("height", afterChanges->getHeight());
    }
    if (beforeChanges->getLastSummonedId() != afterChanges->getLastSummonedId()) {
        result.insert("lastSummonedId", afterChanges->getLastSummonedId());
    }
    if (beforeChanges->getTeamCount() != afterChanges->getTeamCount()) {
        result.insert("teamCount", afterChanges->getTeamCount());
    }
    QJsonArray resources;
    for (int team = 0; team < afterChanges->getTeamCount(); team++) {
        QVector<QPair<core::ResourceType, int>> resVector = afterChanges->getTeamResources(team);
        QJsonArray resource;
        for (auto res : resVector) {
            QJsonObject resPair;
            resPair.insert("type", static_cast<int>(res.first));
            resPair.insert("amount", res.second);
            resource.append(resPair);
        }
        resources.append(resource);
    }
    result.insert("resources", resources);
    QJsonObject object;
    auto iter = afterChanges->getObjects().begin();
    while (iter != afterChanges->getObjects().end()) {
        if (beforeChanges->getObjects().find(iter.key()) == beforeChanges->getObjects().end()) {
            std::optional<QJsonObject> result = Serializer::objectSerializer(*iter.value());
            object.insert(QString::number(iter.key()), result.value());
        } else {
            QJsonObject result = objectPartSerializer(beforeChanges->getObjects()[iter.key()],
                                                      iter.value(),
                                                      keyManager);
            if (result.size() != 0) {
                object.insert(QString::number(iter.key()),
                              result);
            }
        }
        ++iter;
    }
    result.insert("objects", object);
    iter = beforeChanges->getObjects().begin();
    QJsonArray del;
    while (iter != beforeChanges->getObjects().end()) {
        if (afterChanges->getObjects().find(iter.key()) == afterChanges->getObjects().end()) {
            del.push_back(QString::number(iter.key()));
        }
        ++iter;
    }
    result.insert("delete", del);
    return jsonToHashed(result, keyManager);
}

QString utils::SmartSerializer::jsonObjectToString(const QJsonObject& jsonObject) {
    QJsonDocument doc(jsonObject);
    if (prettyPrinting) {
        return doc.toJson(QJsonDocument::Indented);
    }
    return doc.toJson(QJsonDocument::Compact);
}

QString
utils::SmartSerializer::getChanges(const std::shared_ptr<const core::GameWorld>& beforeChanges,
                                   const std::shared_ptr<const core::GameWorld>& afterChanges) {
    KeyManager keyManager(!prettyPrinting);
    return jsonObjectToString(
        gamePartWorldSerializer(beforeChanges, afterChanges, keyManager));
}

void utils::SmartSerializer::partObjectDeserializer(const std::shared_ptr<core::Object>& object,
                                                    QJsonObject changes,
                                                    const utils::KeyManager& keyManager) {
    changes = hashedToJson(changes, keyManager);
    if (changes.find("strategies") != changes.end()) {
        QStringList strategies;
        QJsonArray json;
        json = changes["strategies"].toArray();
        for (const auto& strategy : json) {
            object->getStrategies().push_back(strategy.toString());
        }
    }
    if (changes.find("position") != changes.end()) {
        QJsonObject pos;
        pos = (changes["position"]).toObject();
        QPointF point(pos.value("x").toVariant().toInt(), pos.value("y").toVariant().toInt());
        object->setPosition(point);
    }
    if (changes.find("rotationAngle") != changes.end()) {
        object->setRotationAngle(changes["rotationAngle"].toDouble());
    }
    if (changes.find("sightAngle") != changes.end()) {
        object->setSightAngle(changes["sightAngle"].toDouble());
    }
    if (changes.find("hitbox") != changes.end()) {
        QVector<QPointF> vec;
        QJsonObject pos = changes["hitbox"].toObject();
        auto iterPos = pos.begin();
        QJsonArray xArray = (*iterPos).toArray();
        ++iterPos;
        QJsonArray yArray = (*iterPos).toArray();
        for (const auto& i : xArray) {
            vec.push_back(QPointF(i.toDouble(), 0));
        }
        int it = 0;
        for (const auto& i : yArray) {
            vec[it++].setY(qreal(i.toDouble()));
        }
        object->setHitbox(QPolygonF(vec));
    }
    if (changes.find("typeName") != changes.end()) {
        object->setTypeName(changes["typeName"].toString());
    }
    if (changes.find("attributes") != changes.end()) {
        QJsonObject attributes;
        attributes = changes["attributes"].toObject();
        QLinkedList<std::shared_ptr<core::Attribute> > objectAttributes;
        auto iter = attributes.begin();
        while (iter != attributes.end()) {
            QJsonObject attribute = iter.value().toObject();
            if (attribute.size() == 0) {
                ++iter;
                continue;
            }
            utils::Factory::getPartDeserializer(iter.key())(object->getAttribute(iter.key()),
                                                            attribute, keyManager);
            ++iter;
        }
    }
}

void
utils::SmartSerializer::partGameWorldDeserializer(const std::shared_ptr<core::GameWorld>& gameWorld,
                                                  QJsonObject changes,
                                                  const utils::KeyManager& keyManager) {
    changes = hashedToJson(changes, keyManager);
    if (changes.find("width") != changes.end()) {
        gameWorld->setWidth(changes["width"].toInt());
    }
    if (changes.find("height") != changes.end()) {
        gameWorld->setHeight(changes["height"].toInt());
    }
    if (changes.find("lastSummonedId") != changes.end()) {
        gameWorld->setLastSummonedId(changes["lastSummonedId"].toInt());
    }
    if (changes.find("teamCount") != changes.end()) {
        gameWorld->setTeamCount(changes["teamCount"].toInt());
    }
    if (changes.find("resources") != changes.end()) {
        int team = 0;
        QJsonArray resources = changes["resources"].toArray();
        gameWorld->setTeamCount(resources.size());
        for (const auto& resource : resources) {
            QVector<QPair<core::ResourceType, int>> resVector;
            for (const auto& res : resource.toArray()) {
                auto resObj = res.toObject();
                int type = resObj["type"].toInt();
                int amount = resObj["amount"].toInt();
                resVector.push_back(QPair(static_cast<core::ResourceType>(type), amount));
            }
            gameWorld->setTeamResources(resVector, team);
            ++team;
        }
    }
    if (changes.find("objects") != changes.end()) {
        QJsonObject objects = changes["objects"].toObject();
        auto iter = objects.begin();
        while (iter != objects.end()) {
            if (gameWorld->getObjects().find(iter.key().toLongLong()) !=
                gameWorld->getObjects().end()) {
                partObjectDeserializer(gameWorld->getObjects()[iter.key().toLongLong()],
                                       iter->toObject(), keyManager);
            } else {
                auto result = Serializer::objectDeserializer(iter.value().toObject());
                gameWorld->getObjects()[iter.key().toLongLong()] = std::make_shared<core::Object>(
                    result.value());
            }
            ++iter;
        }
    }
    if (changes.find("delete") != changes.end()) {
        QJsonArray del = changes["delete"].toArray();
        for (const auto& object : del) {
            gameWorld->getObjects().erase(
                    gameWorld->getObjects().find(object.toString().toLongLong()));
        }
    }
}

void utils::SmartSerializer::applyChanges(const std::shared_ptr<core::GameWorld>& gameWorld,
                                          QString changes) {
    KeyManager keyManager(true);
    partGameWorldDeserializer(gameWorld, Serializer::stringToJsonObject(changes).value(),
                              keyManager);
}

QJsonObject
utils::SmartSerializer::jsonToHashed(QJsonObject json, const utils::KeyManager& keyManager) {
    QJsonObject result;
    auto it = json.begin();
    while (it != json.end()) {
        result.insert(keyManager.getHash(it.key()), it.value());
        ++it;
    }
    return result;
}

QJsonObject
utils::SmartSerializer::hashedToJson(QJsonObject json, const utils::KeyManager& keyManager) {
    QJsonObject result;
    auto it = json.begin();
    while (it != json.end()) {
        result.insert(keyManager.getKey(it.key()), it.value());
        ++it;
    }
    return result;
}
