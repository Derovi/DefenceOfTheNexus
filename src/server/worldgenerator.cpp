#include "../core/gameworld.h"

#include "worldgenerator.h"

core::GameWorld* server::world_generator::generate(const GameConfiguration& configuration) {
    core::GameWorld* gameWorld = new core::GameWorld();
    gameWorld->setHeight(configuration.getHeight());
    gameWorld->setWidth(configuration.getWidth());
    return gameWorld;
}
