#ifndef MOVINGPERFORMER_H
#define MOVINGPERFORMER_H

#include <QPointF>
#include <QVector2D>

#include "../../core/gameworld.h"
#include "../../core/object.h"
#include "../../core/attributes/moving.h"

namespace server::moving_performer {

void
move(const std::shared_ptr<core::Object>& object, int64_t timeDelta, const core::Moving& moving);

void moveIfNoObstacles(const std::shared_ptr<core::Object>& object, int64_t timeDelta,
                       const std::shared_ptr<core::GameWorld>& gameWorld,
                       const std::shared_ptr<core::Moving>& moving);

bool isObstacles(const std::shared_ptr<core::Object>& object, int64_t timeDelta,
                 const std::shared_ptr<core::GameWorld>& gameWorld,
                 const std::shared_ptr<core::Moving>& moving);

bool isIntersect(const QPolygonF& polygon,
                 const std::shared_ptr<core::GameWorld>& gameWorld
);

QPointF getNextPosition(const std::shared_ptr<core::Object>& object,
                        int64_t timeDelta, const core::Moving& moving);

}

#endif  // MOVINGPERFORMER_H
