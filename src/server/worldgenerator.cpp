//
// Created by derovi on 3/24/2020.
//

#include "worldgenerator.h"
#include "../core/gameworld.h"

core::GameWorld* WorldGenerator::generate(const GameConfiguration& configuration) {
    core::GameWorld * gameWorld = new core::GameWorld();
    gameWorld->setHeight(configuration.getHeight());
    gameWorld->setWidth(configuration.getWidth());
    return gameWorld;
}
