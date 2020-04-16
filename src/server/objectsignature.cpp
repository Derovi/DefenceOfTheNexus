#include <utility>

#include "../core/attribute.h"
#include "objectsignature.h"

server::ObjectSignature::ObjectSignature(QString typeName, QPolygonF hitbox):
        typeName(typeName), hitbox(std::move(hitbox)) {}

void server::ObjectSignature::setHitbox(const QPolygonF& newHitbox) {
    hitbox = newHitbox;
}

QLinkedList<std::shared_ptr<core::Attribute>>& server::ObjectSignature::getAttributes() {
    return attributes;
}

void
server::ObjectSignature::setAttributes(const QLinkedList<std::shared_ptr<core::Attribute>>& attributes) {
    this->attributes = attributes;
}

QStringList& server::ObjectSignature::getStrategies() {
    return strategies;
}

void server::ObjectSignature::setStrategies(const QStringList& strategies) {
    this->strategies = strategies;
}

bool server::ObjectSignature::hasAttribute(const QString& name) {
    for (std::shared_ptr<core::Attribute> attribute : attributes) {
        if (attribute->getAttributeName() == name) {
            return true;
        }
    }
    return false;
}

const QString& server::ObjectSignature::getTypeName() const {
    return typeName;
}

void server::ObjectSignature::setTypeName(const QString& typeName) {
    this->typeName = typeName;
}

const QLinkedList<std::shared_ptr<core::Attribute>>& server::ObjectSignature::getAttributes() const {
    return attributes;
}

std::shared_ptr<core::Attribute> server::ObjectSignature::getAttribute(const QString& name) {
    for (std::shared_ptr<core::Attribute> attribute : attributes) {
        if (attribute->getAttributeName() == name) {
            return attribute;
        }
    }
    return nullptr;
}

const QPolygonF& server::ObjectSignature::getHitbox() const {
    return hitbox;
}

server::ObjectSignature::ObjectSignature(core::Object object) {
    this->typeName = object.getTypeName();
    this->hitbox = object.getHitbox();
    this->strategies = object.getStrategies();
    for (std::shared_ptr<core::Attribute> attribute : object.getAttributes()) {
        attributes.push_back(attribute->clone());
    }
}

const QStringList& server::ObjectSignature::getStrategies() const {
    return strategies;
}
