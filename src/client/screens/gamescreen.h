#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include "../screen.h"

namespace client {

class GameScreen : public Screen {
  public:
    GameScreen();

  private:
    void onPaused() override;

    void onResumed() override;
};

}

#endif //GAMESCREEN_H
