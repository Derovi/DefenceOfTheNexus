#ifndef PLAYERSLOT_H
#define PLAYERSLOT_H

#include <functional>
#include <QImage>

#include "../widget.h"
#include "textview.h"
#include "imagebutton.h"

namespace client {

class PlayerSlot : public ImageButton {
  public:
    PlayerSlot(QPoint position = QPoint(0, 0), int height = 60,
                int width = 60, bool taken = false, int slotId = 0);

    bool isTaken() const;

    void setTaken(bool taken);

    int getSlotId() const;

    void setSlotId(int slotId);

    void paint(QPainter& painter) override;

  private:
    bool taken;
    int slotId;
    int playerId;
};
}

#endif //PLAYERSLOT_H
