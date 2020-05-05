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

    int getAttackDelay() const;

    int getCurrentDelay() const;

    const QString& getBulletType() const;

    bool isAttacking() const;

    void setDamage(int damage);

    void setAttackRadius(double radius);

    void setAttackDelay(int delay);

    void setCurrentDelay(int delay);

    void setBulletType(const QString& newType);

    void setAttacking(bool attacking);

    void set(const Damaging& properties);

    QString getAttributeName() override;

    std::shared_ptr<Attribute> clone() override;

  private:
    bool attacking;
    int damage;
    int attackDelay;
    int currentDelay;
    double attackRadius;
    QString bulletType;
};

}  // namespace core

#endif  // DAMAGING_H
