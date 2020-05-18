#ifndef GAMECREATIONSCREEN_H
#define GAMECREATIONSCREEN_H

#include <QPushButton>

#include "../screen.h"

namespace client {

class GameCreationScreen : public Screen {
  public:
    GameCreationScreen();

  private:
    void onPaused() override;

    void onResumed() override;

    uint8_t getPlayerCount();

    uint8_t getScreenSize();

};
}

#endif //GAMECREATIONSCREEN_H
