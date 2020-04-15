#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <memory>

#include <QString>

namespace core {

class Attribute {
  public:

    virtual QString getAttributeName() = 0;

    virtual std::shared_ptr<Attribute> clone() = 0;
};

}

#endif //ATTRIBUTE_H
