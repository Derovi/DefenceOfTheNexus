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

    explicit Object(uint64_t id, QString typeName, QPointF position = QPointF(),
                    QPolygonF hitbox = QPolygonF(), float rotationAngle = 0);

    virtual ~Object() = default;

    uint64_t getId() const;

    QPointF getPosition() const;

    QPolygonF getHitbox() const;

    QPolygon getRotatedHitbox() const;

    float getRotationAngle() const;

    const QString& getTypeName() const;

    std::shared_ptr<core::Attribute> getAttribute(const QString& name);

    QLinkedList<std::shared_ptr<Attribute>>& getAttributes();

    const QLinkedList<std::shared_ptr<Attribute>>& getAttributes() const;

    QStringList& getStrategies();

    const QStringList& getStrategies() const;

    void setPosition(const QPointF& newPosition);

    void setId(uint64_t newId);

    void setHitbox(const QPolygonF& hitbox);

    void setRotationAngle(float angle);

    void setTypeName(const QString& typeName);

    void setAttributes(const QLinkedList<std::shared_ptr<Attribute>>& attributes);

    void setStrategies(const QStringList& strategies);

    bool isIntersect(const Object& object) const;

    bool hasAttribute(const QString& name) const;

  private:
    uint64_t id;
    float rotationAngle;
    QString typeName;
    QPointF position;
    QPolygonF hitbox;

    QLinkedList<std::shared_ptr<Attribute>> attributes;
    QStringList strategies;
};

}  // namespace core

#endif  // OBJECT_H
