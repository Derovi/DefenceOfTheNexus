#ifndef DAMAGING_H
#define DAMAGING_H

#include <memory>

#include <QString>

#include "../attribute.h"

namespace core {

class Damaging : public Attribute {
  public:
    inline static const QString attributeName = "damaging";

    Damaging();

    Damaging(int damage, double attackRadius, double attackDelay,
             QString bulletType);

    virtual ~Damaging() = default;

    int getDamage() const;

    double getAttackRadius() const;

    double getAttackDelay() const;

    double getCurrentDelay() const;

    const QString& getBulletType() const;

    void setDamage(int damage);

    void setAttackRadius(double radius);

    void setAttackDelay(double delay);

    void setCurrentDelay(double delay);

    void setBulletType(const QString& newType);

    void set(const Damaging& properties);

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

#endif  // DAMAGING_H
