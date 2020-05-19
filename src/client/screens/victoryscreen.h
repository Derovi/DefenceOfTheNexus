#ifndef VICTORYSCREEN_H
#define VICTORYSCREEN_H

#include <QPushButton>
#include "../screen.h"
namespace client {
class VictoryScreen: public Screen {
  public:
    VictoryScreen();

  private:
    void onPaused() override;

    void onResumed() override;
};

}



#endif //VICTORYSCREEN_H
