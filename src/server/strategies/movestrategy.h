#ifndef MOVESTRATEGY_H
#define MOVESTRATEGY_H

#include "../controllers/databundle.h"
#include "strategy.h"

namespace server {

class MoveStrategy : server::Strategy {
  public:
    explicit MoveStrategy(core::Object* object, DataBundle& dataBundle);

    void tick(core::GameWorld* world, double timeDelta) override;

    QString getName() override;

    static QString name;

  private:

    QVector2D* direction;
    double* speed;
    double* maxSpeed;
};

}

#endif //MOVESTRATEGY_H
