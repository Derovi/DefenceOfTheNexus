#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <memory>

#include <QString>

namespace core {

class Attribute {
  public:
    virtual ~Attribute() = default;

    virtual QString getAttributeName() = 0;

    virtual std::shared_ptr<Attribute> clone() = 0;
};

}  // namespace core

#endif  // ATTRIBUTE_H
