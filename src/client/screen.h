#ifndef SCREEN_H
#define SCREEN_H

#include <QDebug>

#include "widget.h"
#include "sprite.h"

namespace client {

enum ScreenState {
    PAUSED, CURRENT
};

class Screen : public client::Widget {
  public:
    Screen();

    void pause();

    void resume();

    virtual void onPaused() = 0;

    virtual void onResumed() = 0;

    ScreenState getState() const;

    const Sprite& getBackground() const;

    void setBackground(const Sprite& background);

    void draw() override;

    virtual ~Screen() {
        //qDebug() << "destroy screen";
    }

  private:
    ScreenState state = CURRENT;

    Sprite background;
};

}

#endif //SCREEN_H
