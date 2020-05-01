#ifndef OPTIONS_SCREEN_H
#define OPTIONS_SCREEN_H

#include <QPushButton>

#include "../screen.h"

namespace client {

class OptionsScreen : public Screen {
  public:
    OptionsScreen();

  private:
    void onPaused() override;

    void onResumed() override;
};

}

#endif  // OPTIONS_SCREEN_H
