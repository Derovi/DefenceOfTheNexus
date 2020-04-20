#ifndef MOVINGPERFORMER_H
#define MOVINGPERFORMER_H

#include <QPointF>
#include <QVector2D>

#include "../../core/gameworld.h"
#include "../../core/object.h"
#include "../../core/attributes/moving.h"

namespace server::moving_performer {

void move(std::shared_ptr<core::Object> object, double timeDelta, const core::Moving& moving);

void moveIfNoObstacles(std::shared_ptr<core::Object> object, double timeDelta,
                       std::shared_ptr<core::GameWorld> gameWorld,
                       std::shared_ptr<core::Moving> moving);

QPointF getNextPosition(std::shared_ptr<core::Object> object,
                        int timeDelta, const core::Moving& moving);

}

#endif //MOVINGPERFORMER_H
