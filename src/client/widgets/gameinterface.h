#ifndef GAMEINTERFACE_H
#define GAMEINTERFACE_H

#include "../widget.h"

#include "../../core/gameworld.h"
#include "uniticon.h"
#include "healthbar.h"
#include "textview.h"

namespace client {

class GameInterface : public Widget {
  public:
    GameInterface(QPoint position, std::shared_ptr<core::GameWorld> gameWorld, int selectedUnitId = 0);

    void paint(QPainter& painter) override;

  private:
    QImage stoneIcon;

    QImage woodIcon;

    QImage ironIcon;

    std::shared_ptr<core::GameWorld> gameWorld;

    UnitIcon* unitIcon;

    HealthBar* healthBar;

    TextView* stoneView;

    TextView* woodView;

    TextView* ironView;

    int selectedUnitId;
};

}

#endif //GAMEINTERFACE_H
