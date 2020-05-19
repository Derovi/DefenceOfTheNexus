#ifndef MESSAGESCREEN_H
#define MESSAGESCREEN_H

#include <QPushButton>
#include "../screen.h"
namespace client {

enum MessageType{
    ERROR,
    WARNING,
    INFO
};

class MessageScreen: public Screen {
  public:
    MessageScreen(QString text, MessageType type);

  private:
    void onPaused() override;

    void onResumed() override;

};

}

#endif //MESSAGESCREEN_H
