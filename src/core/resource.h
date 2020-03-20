#ifndef RESOURCE_H
#define RESOURCE_H


namespace core {

enum class ResourceType {
    kWood = 0,
    kStone = 1,
    kIron = 2
};

class Resource {
  public:
    Resource() = delete;

    explicit Resource(ResourceType type, int amount = 0);

    ResourceType getType() const;

    int getAmount() const;

    virtual void setAmount(int amount);

  private:
    const ResourceType type;
    int amount;
};

}  // namespace core


#endif // RESOURCE_H
