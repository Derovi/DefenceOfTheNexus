#ifndef MOVESTRATEGY_H
#define MOVESTRATEGY_H

#include "../controllers/databundle.h"
#include "../../core/moving.h"
#include "strategy.h"

namespace server {

class MoveStrategy : public server::Strategy {
  public:
    explicit MoveStrategy(std::shared_ptr<core::Object> object);

    void tick(std::shared_ptr<core::GameWorld> world, double timeDelta) override;

    QString getName() override;

    static QString name;

    ~MoveStrategy();

    QStringList getRequiredAttributes() override;

    QStringList getStartAfter() override;

  private:
    void assign(DataBundle& dataBundle) override;

    static const QStringList requiredAttributes;

    static const QStringList startAfter;

    std::shared_ptr<core::Moving> moving;
};

}

#endif //MOVESTRATEGY_H
