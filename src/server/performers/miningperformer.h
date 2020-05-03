#ifndef MININGPERFORMER_H
#define MININGPERFORMER_H

#include <memory>

#include "../../core/attributes/mining.h"
#include "../../core/attributes/resource.h"
#include "../../core/gameworld.h"
#include "../../core/object.h"

namespace server::mining_performer {

bool isMineable(std::shared_ptr<core::Object> object, std::shared_ptr<core::Mining> mining,
               std::shared_ptr<core::Object> target);

void mine(std::shared_ptr<core::GameWorld> world, std::shared_ptr<core::Object> object,
          std::shared_ptr<core::Mining> mining, std::shared_ptr<core::Object> target,
          int timeDelta);

}  // namespace server::damaging_performer

#endif  // MININGPERFORMER_H
