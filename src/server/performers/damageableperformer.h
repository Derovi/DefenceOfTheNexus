#ifndef DAMAGEABLEPERFORMER_H
#define DAMAGEABLEPERFORMER_H

#include <memory>

#include "../../core/gameworld.h"
#include "../../core/damageable.h"

namespace server::damageable_performer {

void inflictDamage(std::shared_ptr<core::GameWorld> world, std::shared_ptr<core::Object> object,
                   int damage, std::shared_ptr<core::Damageable> damageable);

inline void kill(std::shared_ptr<core::GameWorld> world, std::shared_ptr<core::Object> object);

}

#endif  // DAMAGEABLEPERFORMER_H
