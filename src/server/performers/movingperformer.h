#ifndef MOVINGPERFORMER_H
#define MOVINGPERFORMER_H

#include <QPointF>
#include <QVector2D>

#include "../../core/gameworld.h"
#include "../../core/object.h"
#include "../../core/moving.h"

namespace server::moving_performer {

void move(core::Object* object, double timeDelta, const core::Moving& moving);

void moveIfNoObstacles(core::Object* object, double timeDelta, core::GameWorld* gameWorld,
                       core::Moving* moving);

QPointF getNextPosition(core::Object* object, double timeDelta, const core::Moving& moving);

}

#endif //MOVINGPERFORMER_H
