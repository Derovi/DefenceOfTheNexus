#ifndef OBJECT_H
#define OBJECT_H

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

    explicit Object(uint64_t id, QPointF position = QPointF(), QPolygonF hitbox = QPolygonF(),
                    float rotationAngle = 0);

    virtual ~Object() = default;

    uint64_t getId() const;

    QPointF getPosition() const;

    const QPolygonF& getHitbox() const;

    float getRotationAngle() const;

    virtual void setPosition(const QPointF& newPosition);

    virtual void setId(uint64_t newId);

    virtual void setHitbox(const QPolygonF& hitbox);

    virtual void setRotationAngle(float angle);

    virtual QString getTypeName() = 0;

    bool isIntersect(const Object& object) const;

    QLinkedList<Attribute*>& getAttributes();

    void setAttributes(const QLinkedList<Attribute*>& attributes);

    QStringList& getStrategies();

    void setStrategies(const QStringList& strategies);

    bool hasAttribute(const QString& name);

  private:
    uint64_t id;
    QPointF position;
    QPolygonF hitbox;
    float rotationAngle;

    QLinkedList<Attribute*> attributes;
    QStringList strategies;

};

}  // namespace core

#endif // OBJECT_H
