#ifndef LOSSSCREEN_H
#define LOSSSCREEN_H

#include <QPushButton>
#include "../screen.h"

namespace client {

class LossScreen : public Screen {
  public:
    LossScreen();

  private:
    void onPaused() override;

    void onResumed() override;
};

}

#endif //LOSSSCREEN_H
