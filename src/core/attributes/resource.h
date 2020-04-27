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

    explicit Resource(ResourceType type, int amount = 0);

    ResourceType getType() const;

    int getAmount() const;

    void setAmount(int amount);

    void setType(ResourceType newType);

    QString getAttributeName() override;

    std::shared_ptr<Attribute> clone() override;

  private:
    ResourceType type;
    int amount;
};

}  // namespace core

#endif  // RESOURCE_H
