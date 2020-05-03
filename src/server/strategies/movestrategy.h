#ifndef MOVESTRATEGY_H
#define MOVESTRATEGY_H

#include "../controllers/databundle.h"
#include "../../core/attributes/moving.h"
#include "strategy.h"

namespace server {

class MoveStrategy : public server::Strategy {
  public:
    explicit MoveStrategy(std::shared_ptr<core::Object> object);

    ~MoveStrategy() override = default;

    void tick(std::shared_ptr<core::GameWorld> world, int timeDelta) override;

    QString getName() override;

    static QString name;

    QStringList getRequiredAttributes() override;

    QStringList getStartAfter() override;

    void assign(DataBundle& dataBundle) override;

  private:
    static const QStringList requiredAttributes;

    static const QStringList startAfter;

    std::shared_ptr<core::Moving> moving;
};

}

#endif //MOVESTRATEGY_H
