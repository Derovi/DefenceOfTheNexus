#ifndef GAMEINTERFACE_H
#define GAMEINTERFACE_H

#include "../widget.h"

#include "../../core/gameworld.h"
#include "uniticon.h"

namespace client {

class GameInterface : public Widget {
  public:
    GameInterface(QPoint position, std::shared_ptr<core::GameWorld> gameWorld, int selectedUnitId = 0);

    void paint(QPainter& painter) override;

  private:
    std::shared_ptr<core::GameWorld> gameWorld;

    UnitIcon* unitIcon;

    int selectedUnitId;
};

}

#endif //GAMEINTERFACE_H
