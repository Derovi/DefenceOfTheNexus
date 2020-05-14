#ifndef BUILDER_H
#define BUILDER_H

#include <memory>

#include <QString>
#include <QtCore/QStringList>

#include "../attribute.h"

namespace core {

class Builder : public Attribute {
  public:
    inline static const QString attributeName = "builder";

    Builder();

    explicit Builder(const QStringList& buildList);

    ~Builder() override = default;

    QString getAttributeName() override;

    std::shared_ptr<Attribute> clone() override;

    const QStringList& getBuildList() const;

    void setBuildList(const QStringList& buildList);

    bool operator==(core::Builder object);

  private:
    QStringList buildList;
};

}  // namespace core

#endif  // BUILDER_H
