#ifndef DAMAGEABLEPERFORMER_H
#define DAMAGEABLEPERFORMER_H

#include <memory>

#include "../../core/gameworld.h"
#include "../../core/attributes/damageable.h"

namespace server::damageable_performer {

void inflictDamage(std::shared_ptr<core::GameWorld> world, std::shared_ptr<core::Object> object,
                   std::shared_ptr<core::Damageable> damageable, int damage);

inline void kill(std::shared_ptr<core::GameWorld> world, std::shared_ptr<core::Object> object);

}

#endif  // DAMAGEABLEPERFORMER_H
