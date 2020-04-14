#ifndef WORLDGENERATOR_H
#define WORLDGENERATOR_H

#include "../core/gameworld.h"

#include "gameconfiguration.h"

// class is responsible for random world generation.
// base center is always in the middle

namespace server::world_generator {

std::shared_ptr<core::GameWorld> generate(const GameConfiguration& configuration);

}

#endif //WORLDGENERATOR_H
