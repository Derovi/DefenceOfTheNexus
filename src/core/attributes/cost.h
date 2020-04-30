#ifndef COST_H
#define COST_H

#include <memory>
#include <QMap>
#include <QtCore/QHash>
#include "../object.h"

namespace core {

struct ResCost {
    int iron;
    int wood;
    int stone;
};

class Cost : public Attribute {
  public:
    Cost();

    explicit Cost(QMap<std::shared_ptr<core::Object>, core::ResCost>& hashMap);

    QMap<std::shared_ptr<core::Object>, core::ResCost>& getCost();

    void setCost(QMap<std::shared_ptr<core::Object>, core::ResCost>);

    static QString attributeName;

    QString getAttributeName() override;

    std::shared_ptr<Attribute> clone() override;


  private:
    QMap<std::shared_ptr<core::Object>, core::ResCost> cost;
};

} // namespace core


#endif //COST_H
