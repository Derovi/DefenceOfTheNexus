#ifndef DAMAGEABLE_H
#define DAMAGEABLE_H

#include <QString>

#include "attribute.h"

namespace core {

class Damageable : public Attribute {
  public:
    Damageable();

    Damageable(int health, int maxHealth);

    virtual ~Damageable() = default;

    int getHealth() const;

    int getMaxHealth() const;

    virtual void setHealth(int health);

    virtual void setMaxHealth(int maxHealth);

    virtual void set(const Damageable& properties);

    QString getAttributeName() override;

    static QString attributeName;

  private:
    int health;
    int maxHealth;
};

}  // namespace core

#endif // DAMAGEABLE_H
