#ifndef DAMAGEABLE_H
#define DAMAGEABLE_H

namespace core {

class Damageable {
  public:
    Damageable();

    Damageable(int health, int maxHealth);

    virtual ~Damageable() = default;

    int getHealth() const;

    int getMaxHealth() const;

    virtual void setHealth(int health);

    virtual void setMaxHealth(int maxHealth);

    virtual void set(const Damageable& properties);

  private:
    int health;
    int maxHealth;
};

}  // namespace core

#endif // DAMAGEABLE_H
