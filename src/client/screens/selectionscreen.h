#ifndef SELECTIONSCREEN_H
#define SELECTIONSCREEN_H

#include <QPushButton>

#include "../screen.h"
#include "../network/multiplayerinterface.h"
#include "../widgets/playerslot.h"

namespace client {

class SelectionScreen : public Screen {
  public:
    explicit SelectionScreen(std::shared_ptr<MultiplayerInterface> multiplayerInterface, int playersCount);

    void updateSlots(QVector <QString> list);

    int getMyPlayerId();

  private:
    void onPaused() override;

    void onResumed() override;

    std::shared_ptr<MultiplayerInterface> multiplayerInterface;

    int playersCount;
    QVector<std::shared_ptr<PlayerSlot>> playersSlots;
};

}

#endif //SELECTIONSCREEN_H
