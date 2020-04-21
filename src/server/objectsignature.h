#ifndef OBJECTSIGNATURE_H
#define OBJECTSIGNATURE_H

#include <memory>

#include <QLinkedList>
#include <QtGlobal>
#include <QPointF>
#include <QPolygonF>
#include <QtCore/QStringList>

#include "../core/object.h"
#include "../core/attribute.h"

namespace server {

class ObjectSignature {
  public:
    ObjectSignature() = delete;

    // Copies current object attributes states.
    // Example: if object has 47/100 hp, then objects,
    // summoned with creates signature will have 47/100 hp.
    explicit ObjectSignature(core::Object object);

    explicit ObjectSignature(QString typeName,
                             QPolygonF hitbox = QPolygonF());

    virtual ~ObjectSignature() = default;

    const QPolygonF& getHitbox() const;

    void setHitbox(const QPolygonF& hitbox);

    const QString& getTypeName() const;

    void setTypeName(const QString& typeName);

    QLinkedList<std::shared_ptr<core::Attribute>>& getAttributes();

    const QLinkedList<std::shared_ptr<core::Attribute>>& getAttributes() const;

    void setAttributes(const QLinkedList<std::shared_ptr<core::Attribute>>& attributes);

    QStringList& getStrategies();

    const QStringList& getStrategies() const;

    void setStrategies(const QStringList& strategies);

    bool hasAttribute(const QString& name);

    std::shared_ptr<core::Attribute> getAttribute(const QString& name);

  private:
    QString typeName;
    QPolygonF hitbox;

    QLinkedList<std::shared_ptr<core::Attribute>> attributes;
    QStringList strategies;
};

}  // namespace server


#endif //OBJECTSIGNATURE_H
