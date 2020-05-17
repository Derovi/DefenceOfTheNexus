#ifndef SETTINGSSCREEN_H
#define SETTINGSSCREEN_H
#include <QPushButton>

#include "../screen.h"

namespace client {

class SettingScreen : public Screen {
  public:
    SettingScreen();

  private:
    void onPaused() override;

    void onResumed() override;
};

}

#endif //SETTINGSSCREEN_H
