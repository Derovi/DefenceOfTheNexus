#ifndef NETWORKSCREEN_H
#define NETWORKSCREEN_H
#include <QPushButton>

#include "../screen.h"

namespace client {

class NetworkScreen : public Screen {
  public:
    NetworkScreen();

  private:
    void onPaused() override;

    void onResumed() override;
};

}

#endif //NETWORKSCREEN_H
