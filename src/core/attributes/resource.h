#ifndef RESOURCE_H
#define RESOURCE_H

#include <memory>

#include <QString>

#include "../attribute.h"

namespace core {

enum class ResourceType {
    kWood,
    kStone,
    kIron
};

class Resource : public Attribute {
  public:
    inline static const QString attributeName = "resource";

    Resource() = delete;

    explicit Resource(ResourceType type, int amount = 0, int maxAmount = 0,
                      double miningSpeedModifier = 1);

    int getAmount() const;

    ResourceType getType() const;

    double getMiningSpeedModifier() const;

    void setAmount(int amount);

    void setType(ResourceType newType);

    void setMiningSpeedModifier(double modifier);

    int mine(int speed);

    int getMaxAmount() const;

    void setMaxAmount(int maxAmount);

    QString getAttributeName() override;

    std::shared_ptr<Attribute> clone() override;

    bool operator==(const core::Resource&) const;

    bool operator==(const core::Resource);


  private:
    ResourceType type;

    double miningSpeedModifier;

    int amount;
    int maxAmount;
};

}  // namespace core

#endif  // RESOURCE_H
