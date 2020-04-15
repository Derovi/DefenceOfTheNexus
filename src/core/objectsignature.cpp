#include <utility>

#include "attribute.h"
#include "objectsignature.h"

core::ObjectSignature::ObjectSignature(QString typeName, QPolygonF hitbox):
        typeName(typeName), hitbox(std::move(hitbox)) {}

void core::ObjectSignature::setHitbox(const QPolygonF& newHitbox) {
    hitbox = newHitbox;
}

QLinkedList<std::shared_ptr<core::Attribute>>& core::ObjectSignature::getAttributes() {
    return attributes;
}

void
core::ObjectSignature::setAttributes(const QLinkedList<std::shared_ptr<Attribute>>& attributes) {
    this->attributes = attributes;
}

QStringList& core::ObjectSignature::getStrategies() {
    return strategies;
}

void core::ObjectSignature::setStrategies(const QStringList& strategies) {
    this->strategies = strategies;
}

bool core::ObjectSignature::hasAttribute(const QString& name) {
    for (std::shared_ptr<Attribute> attribute : attributes) {
        if (attribute->getAttributeName() == name) {
            return true;
        }
    }
    return false;
}

const QString& core::ObjectSignature::getTypeName() const {
    return typeName;
}

void core::ObjectSignature::setTypeName(const QString& typeName) {
    this->typeName = typeName;
}

const QLinkedList<std::shared_ptr<core::Attribute>>& core::ObjectSignature::getAttributes() const {
    return attributes;
}

std::shared_ptr<core::Attribute> core::ObjectSignature::getAttribute(const QString& name) {
    for (std::shared_ptr<Attribute> attribute : attributes) {
        if (attribute->getAttributeName() == name) {
            return attribute;
        }
    }
    return nullptr;
}

const QPolygonF& core::ObjectSignature::getHitbox() const {
    return hitbox;
}

core::ObjectSignature::ObjectSignature(core::Object object) {
    this->typeName = object.getTypeName();
    this->hitbox = object.getHitbox();
    this->strategies = object.getStrategies();
    for (std::shared_ptr<Attribute> attribute : object.getAttributes()) {
        attributes.push_back(attribute->clone());
    }
}
