#ifndef MENUSCREEN_H
#define MENUSCREEN_H

#include <QPushButton>
#include "../screen.h"

namespace client {

class MenuScreen : public Screen {
  public:
    MenuScreen();
  private:
    void onPaused() override;

    void onResumed() override;

    QPushButton* button;
};

}

#endif //MENUSCREEN_H
