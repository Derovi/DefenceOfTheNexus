#ifndef GAMEINTERFACE_H
#define GAMEINTERFACE_H

#include "../widget.h"

#include "../../core/gameworld.h"
#include "uniticon.h"
#include "healthbar.h"
#include "textview.h"
#include "imagebutton.h"
#include "buildslot.h"

namespace client {

class GameInterface : public Widget {
  public:
    GameInterface(QPoint position, int height, int width,
                  std::shared_ptr<core::GameWorld> gameWorld, int selectedUnitId = 0);

    void paint(QPainter& painter) override;

    int getSelectedUnitId() const;

    void setSelectedUnitId(int selectedUnitId);

  private:
    QImage stoneIcon;
    QImage woodIcon;
    QImage ironIcon;

    QImage damageIcon;
    QImage miningIcon;
    QImage armorIcon;

    std::shared_ptr<core::GameWorld> gameWorld;

    QVector<BuildSlot*> buildSlots;

    UnitIcon* unitIcon;
    HealthBar* healthBar;

    TextView* stoneView;
    TextView* woodView;
    TextView* ironView;

    TextView* damageView;
    TextView* miningView;
    TextView* armorView;

    ImageButton* aiButton;
    ImageButton* stopButton;
    ImageButton* killButton;

    int selectedUnitId;
};

}

#endif //GAMEINTERFACE_H
