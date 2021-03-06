#ifndef GAMEINTERFACE_H
#define GAMEINTERFACE_H

#include "../widget.h"

#include "../../core/gameworld.h"
#include "uniticon.h"
#include "healthbar.h"
#include "textview.h"
#include "imagebutton.h"
#include "buildslot.h"
#include "minimap.h"

namespace client {

class GameInterface : public Widget {
  public:
    GameInterface(QPoint position, int height, int width,
                  std::shared_ptr<core::GameWorld> gameWorld, int selectedUnitId = 0);

    void paint(QPainter& painter) override;

    int getSelectedUnitId() const;

    void setSelectedUnitId(int selectedUnitId);

    void init();

  private:
    QImage stoneIcon;
    QImage woodIcon;
    QImage ironIcon;

    QImage damageIcon;
    QImage miningIcon;
    QImage armorIcon;
    QImage speedIcon;

    std::shared_ptr<core::GameWorld> gameWorld;

    QVector<BuildSlot*> buildSlots;

    UnitIcon* unitIcon;
    HealthBar* healthBar;
    MiniMap* miniMap;

    TextView* stoneView;
    TextView* woodView;
    TextView* ironView;

    TextView* damageView;
    TextView* miningView;
    TextView* armorView;
    TextView* speedView;

    ImageButton* aiButton;
    ImageButton* stopButton;
    ImageButton* killButton;

    int selectedUnitId;
};

}

#endif //GAMEINTERFACE_H
