#ifndef MENUSCREEN_H
#define MENUSCREEN_H

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

#endif //MENUSCREEN_H
