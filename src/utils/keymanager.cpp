#include "keymanager.h"

void utils::KeyManager::registerKeys() {
    addKey("maxHealth");
    addKey("id");
    addKey("position");
    addKey("rotationAngle");
    addKey("strategies");
    addKey("hitbox");
    addKey("typeName");
    addKey("attributes");
    addKey("resourceType");
    addKey("amount");
    addKey("maxAmount");
    addKey("miningSpeedModifier");
    addKey("damage");
    addKey("radius");
    addKey("delay");
    addKey("bulletType");
    addKey("attacking");
    addKey("list");
    addKey("health");
    addKey("maxHealth");
    addKey("direction");
    addKey("maxSpeed");
    addKey("speed");
    addKey("miningSpeed");
    addKey("miningDelay");
    addKey("miningRadius");
    addKey("mining");
    addKey("width");
    addKey("height");
    addKey("type");
    addKey("resources");
    addKey("objects");
    addKey("arguments");
    addKey("wallType");
    addKey("all");
}

utils::KeyManager::KeyManager(bool hash) {
    hashing = hash;
}

QString utils::KeyManager::hash = "a";
QMap<QString, QString>utils::KeyManager::keyToHash;
QMap<QString, QString>utils::KeyManager::hashToKey;

QString utils::KeyManager::addKey(QString key) {
    keyToHash[key] = hash;
    hashToKey[hash] = key;
    if (hash == "z") {
        hash = "A";
        return keyToHash[key];
    }
    if (hash == "Z") {
        hash = "aa";
        return keyToHash[key];
    }
    if (hash.back() == 'z') {
        hash.back() = 'a';
        hash[0].unicode()++;
    } else {
        hash[1].unicode()++;
    }
    return keyToHash[key];
}

QString utils::KeyManager::getHash(QString key) {
    return hashToKey[key];
}

QString utils::KeyManager::getKey(QString hash) {
    return keyToHash[hash];
}
