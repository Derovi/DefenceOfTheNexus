#ifndef SELECTIONSCREEN_H
#define SELECTIONSCREEN_H
#include <QPushButton>

#include "../screen.h"

namespace client {

class SelectionScreen : public Screen {
  public:
    SelectionScreen();

  private:
    void onPaused() override;

    void onResumed() override;
};

}

#endif //SELECTIONSCREEN_H
