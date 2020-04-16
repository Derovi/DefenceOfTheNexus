#ifndef DAMAGEABLE_H
#define DAMAGEABLE_H

#include <memory>
#include <QString>
#include <bits/shared_ptr.h>

#include "../attribute.h"

namespace core {

class Damageable : public Attribute {
  public:
    Damageable();

    Damageable(int health, int maxHealth);

    virtual ~Damageable() = default;

    int getHealth() const;

    int getMaxHealth() const;

    void setHealth(int health);

    void setMaxHealth(int maxHealth);

    void set(const Damageable& properties);

    QString getAttributeName() override;

    std::shared_ptr<Attribute> clone() override;

    static const QString attributeName;

  private:
    int health;
    int maxHealth;
};

}  // namespace core

#endif // DAMAGEABLE_H