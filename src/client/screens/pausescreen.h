#ifndef PAUSESCREEN_H
#define PAUSESCREEN_H

#include <QPushButton>
#include "../screen.h"

namespace client {

class PauseScreen : public Screen {
  public:
    PauseScreen();

  private:
    void onPaused() override;

    void onResumed() override;
};

}

#endif //PAUSESCREEN_H
