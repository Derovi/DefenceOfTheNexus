#ifndef SCREEN_H
#define SCREEN_H

#include "widget.h"

namespace client {

enum ScreenState {
    PAUSED, CURRENT
};

class Screen : public client::Widget {
  public:
    Screen() {}

    void pause();

    void resume();

    virtual void onPaused() = 0;

    virtual void onResumed() = 0;

    ScreenState getState() const;

  private:
    ScreenState state = CURRENT;
};

}

#endif //SCREEN_H
