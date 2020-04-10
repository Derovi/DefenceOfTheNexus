#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <QString>

namespace core {

class Attribute {
  public:

    virtual QString getAttributeName() = 0;
};

}

#endif //ATTRIBUTE_H
