#ifndef MOVESTRATEGY_H
#define MOVESTRATEGY_H

#include "../controllers/databundle.h"
#include "../../core/moving.h"
#include "strategy.h"

namespace server {

class MoveStrategy : public server::Strategy {
  public:
    explicit MoveStrategy(core::Object* object, DataBundle& dataBundle);

    void tick(core::GameWorld* world, double timeDelta) override;

    QString getName() override;

    static QString name;

    ~MoveStrategy() override;

  private:
    void assign(DataBundle& dataBundle) override;

    core::Moving* moving;
};

}

#endif //MOVESTRATEGY_H
