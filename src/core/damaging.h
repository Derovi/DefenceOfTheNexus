#ifndef DAMAGING_H
#define DAMAGING_H

#include <QString>

namespace core {

class Damaging {
  public:
    Damaging();

    Damaging(int damage, double attackRadius, double attackDelay,
             QString bulletType);

    virtual ~Damaging() = default;

    int getDamage() const;

    double getAttackRadius() const;

    double getAttackDelay() const;

    virtual void setDamage(int damage);

    virtual void setAttackRadius(double radius);

    virtual void setAttackDelay(double delay);

    virtual void set(const Damaging& properties);

  private:
    int damage;
    double attackRadius;
    double attackDelay;
    QString bulletType;
};

}  // namespace core

#endif // DAMAGING_H
