#ifndef SELECTIONSCREEN_H
#define SELECTIONSCREEN_H
#include <QPushButton>

#include "../screen.h"
#include "../widgets/playerslot.h"

namespace client {

class SelectionScreen : public Screen {
  public:
    SelectionScreen(int playersCount);

    void updateSlots(QVector <QString> list);

    int getMyPlayerId();

  private:
    void onPaused() override;

    void onResumed() override;

    int playersCount;
    QVector<std::shared_ptr<PlayerSlot>> playersSlots;

};

}

#endif //SELECTIONSCREEN_H
