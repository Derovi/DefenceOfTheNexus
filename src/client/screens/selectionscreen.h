#ifndef SELECTIONSCREEN_H
#define SELECTIONSCREEN_H

#include <QPushButton>

#include "../screen.h"
#include "../network/multiplayerinterface.h"

namespace client {

class SelectionScreen : public Screen {
  public:
    explicit SelectionScreen(std::shared_ptr<MultiplayerInterface> multiplayerInterface);

  private:
    void onPaused() override;

    void onResumed() override;

    std::shared_ptr<MultiplayerInterface> multiplayerInterface;
};

}

#endif //SELECTIONSCREEN_H
