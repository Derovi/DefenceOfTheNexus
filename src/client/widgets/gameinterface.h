#ifndef GAMEINTERFACE_H
#define GAMEINTERFACE_H

#include "../widget.h"

#include "../../core/gameworld.h"

namespace client {

class GameInterface : public Widget {
  public:
    GameInterface(QPoint position, std::shared_ptr<core::GameWorld> gameWorld, int selectedUnitId = 0);

  private:
    std::shared_ptr<core::GameWorld> gameWorld;

    int selectedUnitId;
};

}

#endif //GAMEINTERFACE_H
