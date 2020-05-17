#ifndef BULLET_H
#define BULLET_H

#include <QPointF>

#include "../attribute.h"
#include "../object.h"

namespace core {

class Bullet : public Attribute {
  public:
    inline static const QString attributeName = "bullet";

    Bullet();

    ~Bullet() override = default;

    QString getAttributeName() override;

    std::shared_ptr<Attribute> clone() override;

    int getDamage() const;

    double getRange() const;

    uint64_t getOwnerId() const;

    QPointF getShooterPos() const;

    void setDamage(int damage);

    void setRange(double range);

    void setOwnerId(uint64_t id);

    void setShooterPos(QPointF pos);

    void setOwner(std::shared_ptr<core::Object> shooter);

    bool operator==(const Bullet& bullet) const;

  private:
    int damage;
    double range;
    uint64_t ownerId;
    QPointF shooterPos;
};

}  // namespace core

#endif  // BULLET_H
