#include "../core/gameworld.h"

#include "worldgenerator.h"

std::shared_ptr<core::GameWorld> server::world_generator::generate(const GameConfiguration& configuration) {
    std::shared_ptr<core::GameWorld> gameWorld(new core::GameWorld());
    gameWorld->setHeight(configuration.getHeight());
    gameWorld->setWidth(configuration.getWidth());
    return gameWorld;
}
