#ifndef RESOURCE_H
#define RESOURCE_H

#include <QString>
#include "attribute.h"

namespace core {

enum class ResourceType {
    kWood,
    kStone,
    kIron
};

class Resource : Attribute {
  public:
    Resource() = delete;

    explicit Resource(ResourceType type, int amount = 0);

    ResourceType getType() const;

    int getAmount() const;

    void setAmount(int amount);

    void setType(ResourceType newType);

    static QString attributeName;

    QString getAttributeName() override;

  private:
    ResourceType type;
    int amount;
};

}  // namespace core

#endif // RESOURCE_H
