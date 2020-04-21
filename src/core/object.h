#ifndef OBJECT_H
#define OBJECT_H

#include <memory>

#include <QLinkedList>
#include <QtGlobal>
#include <QPointF>
#include <QPolygonF>
#include <QtCore/QStringList>

#include "attribute.h"

namespace core {

class Object {
  public:
    Object() = delete;

    explicit Object(uint64_t id, QString typeName, QPointF position = QPointF(), QPolygonF hitbox = QPolygonF(),
                    float rotationAngle = 0);

    virtual ~Object() = default;

    uint64_t getId() const;

    QPointF getPosition() const;

    const QPolygonF& getHitbox() const;

    float getRotationAngle() const;

    void setPosition(const QPointF& newPosition);

    void setId(uint64_t newId);

    void setHitbox(const QPolygonF& hitbox);

    void setRotationAngle(float angle);

    const QString& getTypeName() const;

    void setTypeName(const QString& typeName);

    bool isIntersect(const Object& object) const;

    QLinkedList<std::shared_ptr<Attribute>>& getAttributes();

    const QLinkedList<std::shared_ptr<Attribute>>& getAttributes() const;

    void setAttributes(const QLinkedList<std::shared_ptr<Attribute>>& attributes);

    QStringList& getStrategies();

    const QStringList& getStrategies() const;

    void setStrategies(const QStringList& strategies);

    bool hasAttribute(const QString& name) const;

    std::shared_ptr<core::Attribute> getAttribute(const QString& name);

  private:
    QString typeName;
    uint64_t id;
    QPointF position;
    QPolygonF hitbox;
    float rotationAngle;

    QLinkedList<std::shared_ptr<Attribute>> attributes;
    QStringList strategies;
};

}  // namespace core

#endif // OBJECT_H
