#ifndef SPRITE_H
#define SPRITE_H

#include <QPixmap>
#include <QPainter>

namespace client {

class Sprite {
  public:
    Sprite(const QPixmap& source, int rows = 1, int columns = 1, int framesPerSec = 30);

    void update(uint64_t timeDeltaMSec = 42);

    void draw(QPainter& painter, const QRect& destination);

    QRect getFrameBounds() const;

    int getFrameCount() const;

    void jump(int frameNumber);

    int getCurrentFrame() const;

    int getRows() const;

    int getColumns() const;

    int getFramesPerSec() const;

    int getFrameWidth() const;

    int getFrameHeight() const;

    void setFramesPerSec(int framesPerSec);

  private:
    QPixmap source;

    int framesPerSec;

    int rows;

    int columns;

    uint64_t lastUpdateTime;
};

}

#endif //SPRITE_H