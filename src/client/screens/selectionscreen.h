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

  private:
    void onPaused() override;

    void onResumed() override;

    void requestSlot(uint8_t slotId);

    void requestNicknameChange(const QString& nickname);

    void updateSlots(QVector<QString> list);

    int getMyPlayerId();

    std::shared_ptr<MultiplayerInterface> multiplayerInterface;

    int playersCount;
    QVector<std::shared_ptr<PlayerSlot>> playersSlots;

  private slots:
    void onInited();
};

}

#endif //SELECTIONSCREEN_H
