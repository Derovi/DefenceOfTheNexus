#ifndef DAMAGEABLE_H
#define DAMAGEABLE_H

#include <memory>

#include <QString>

#include "../attribute.h"

namespace core {

class Damageable : public Attribute {
  public:
    inline static const QString attributeName = "damageable";

    Damageable();

    Damageable(int health, int maxHealth);

    ~Damageable() override = default;

    int getHealth() const;

    int getMaxHealth() const;

    void setHealth(int health);

    void setMaxHealth(int maxHealth);

    void set(const Damageable& properties);

    QString getAttributeName() override;

    std::shared_ptr<Attribute> clone() override;

    bool operator==(core::Damageable object);

  private:
    int health;
    int maxHealth;
};

}  // namespace core

#endif  // DAMAGEABLE_H
