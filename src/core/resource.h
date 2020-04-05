#ifndef RESOURCE_H
#define RESOURCE_H

namespace core {

enum class ResourceType {
    kWood,
    kStone,
    kIron
};

class Resource {
  public:
    Resource() = delete;

    explicit Resource(ResourceType type, int amount = 0);

    ResourceType getType() const;

    int getAmount() const;

    void setAmount(int amount);

    void setType(ResourceType newType);

  private:
    const ResourceType type;
    int amount;
};

}  // namespace core

#endif // RESOURCE_H
