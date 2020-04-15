#ifndef DAMAGING_H
#define DAMAGING_H

#include <QString>
#include <bits/shared_ptr.h>

#include "attribute.h"

namespace core {

class Damaging : public Attribute {
  public:
    Damaging();

    Damaging(int damage, double attackRadius, double attackDelay,
             QString bulletType);

    virtual ~Damaging() = default;

    int getDamage() const;

    double getAttackRadius() const;

    double getAttackDelay() const;

    double getCurrentDelay() const;

    const QString& getBulletType() const;

    virtual void setDamage(int damage);

    virtual void setAttackRadius(double radius);

    virtual void setAttackDelay(double delay);

    virtual void setCurrentDelay(double delay);

    virtual void setBulletType(const QString& newType);

    virtual void set(const Damaging& properties);

    static QString attributeName;

    QString getAttributeName() override;

    std::shared_ptr<Attribute> clone() override;

  private:
    int damage;
    double attackRadius;
    double attackDelay;
    double currentDelay;
    QString bulletType;
};

}  // namespace core

#endif // DAMAGING_H
