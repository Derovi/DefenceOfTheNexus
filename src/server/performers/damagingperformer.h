#ifndef DAMAGINGPERFORMER_H
#define DAMAGINGPERFORMER_H

#include <memory>

#include "../../core/object.h"
#include "../../core/attributes/damaging.h"
#include "../../core/gameworld.h"

namespace server::damaging_performer {

// checks whether attackRadius < distanceToTarget
bool isDamageable(std::shared_ptr<core::Object> object, std::shared_ptr<core::Damaging> damaging,
                  std::shared_ptr<core::Object> target);

void damage(std::shared_ptr<core::GameWorld> world, std::shared_ptr<core::Object> object,
            std::shared_ptr<core::Damaging> damaging, std::shared_ptr<core::Object> target,
            int timeDelta);
}  // namespace server::damaging_performer

#endif  // DAMAGINGPERFORMER_H
