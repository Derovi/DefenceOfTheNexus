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
                int width = 60);

  private:
    bool taken;


};

}

#endif //PLAYERSLOT_H
