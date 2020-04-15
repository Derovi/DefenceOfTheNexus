#ifndef DAMAGINGPERFORMER_H
#define DAMAGINGPERFORMER_H

#include <memory>

#include "../../core/object.h"
#include "../../core/damaging.h"
#include "../../core/gameworld.h"

namespace server::damaging_performer {

void damage(std::shared_ptr<core::GameWorld> world, std::shared_ptr<core::Object> object,
            std::shared_ptr<core::Damaging> damaging, double timeDelta);

}  // namespace server::damaging_performer

#endif  // DAMAGINGPERFORMER_H
