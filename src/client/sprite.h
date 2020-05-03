#ifndef SPRITE_H
#define SPRITE_H

#include <QPixmap>
#include <QPainter>

#include "spritedescription.h"

namespace client {

class Sprite {
  public:
    Sprite() : rows(0), columns(0) {}

    explicit Sprite(const QPixmap& source, int rows = 1, int columns = 1, int framesPerSec = 30);

    explicit Sprite(const SpriteDescription& spriteDescription);

    virtual ~Sprite() = default;

    void update(uint64_t timeDeltaMSec = 42);

    void draw(QPainter& painter, const QRect& destination);

    bool isNull();

    void pause();

    void resume();

    QRect getFrameBounds() const;

    int getFrameCount() const;

    void jump(int frameNumber);

    int getCurrentFrame() const;

    int getRows() const;

    int getColumns() const;

    int getFramesPerSec() const;

    int getFrameWidth() const;

    int getFrameHeight() const;

    int64_t getAnimationDurationMSec() const;

    void setFramesPerSec(int framesPerSec);

    bool isReverseDirection() const;

    void setReverseDirection(bool reverseDirection);

    const QPixmap& getSource() const;

    bool isPaused() const;

    bool isMirroring() const;

    void setMirroring(bool mirroring);

    int getFirstFrame() const;

    void setFirstFrame(int firstFrame);

    int getLastFrame() const;

    void setLastFrame(int lastFrame);

    uint64_t getLastUpdateTime() const;

    bool isBackAndForthMode() const;

    void setBackAndForthMode(bool backAndForthMode);

  private:
    QPixmap source;

    int framesPerSec;

    int rows;

    int columns;

    int64_t lastUpdateTime;

    bool reverseDirection;

    bool paused;

    bool mirroring;

    int firstFrame;

    int lastFrame;

    bool backAndForthMode;
};

}

#endif  // SPRITE_H
