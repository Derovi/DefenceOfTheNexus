#include "damageableperformer.h"

namespace server::damageable_performer {

void inflictDamage(std::shared_ptr<core::GameWorld> world, std::shared_ptr<core::Object> object,
                   std::shared_ptr<core::Damageable> damageable, int damage) {
    damageable->setHealth(damageable->getHealth() - damage);
    if (damageable->getHealth() < 0) {
        kill(world, object);
    }
}

void kill(std::shared_ptr<core::GameWorld> world, std::shared_ptr<core::Object> object) {
    world->getObjects().remove(object->getId());
}

}  // namespace server::damageable_performer
