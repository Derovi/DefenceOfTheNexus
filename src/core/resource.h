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

    Resource(const Resource& what_copy);

    ResourceType getType() const;

    int getAmount() const;

    void setAmount(int amount);

    void setType(ResourceType new_type);


  private:
    ResourceType type;  //  Deleted const because of addResource function,that is getting a reference to an Object
                        // and writes all changes directly to an Object
    int amount;
};

}  // namespace core

#endif // RESOURCE_H
