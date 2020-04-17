#include "sprite.h"

Sprite::Sprite(const QPixmap& source, int rows, int columns, int framesPerSec):
        source(source), rows(rows), columns(columns), framesPerSec(framesPerSec),
        lastUpdateTime(0) {}

int Sprite::getRows() const {
    return rows;
}

int Sprite::getColumns() const {
    return columns;
}

int Sprite::getCurrentFrame() const {
    return lastUpdateTime / framesPerSec % getFrameCount();
}

int Sprite::getFrameCount() const {
    return rows * columns;
}

int Sprite::getFramesPerSec() const {
    return framesPerSec;
}

void Sprite::setFramesPerSec(int framesPerSec) {
    int currentFrame = getCurrentFrame();
    this->framesPerSec = framesPerSec;
    jump(currentFrame);
}

int Sprite::getFrameWidth() const {
    return source.width() / columns;
}

int Sprite::getFrameHeight() const {
    return source.height() / rows;
}

QRect Sprite::getFrameBounds() const {
    int row = getCurrentFrame() / columns;
    int column = getCurrentFrame() % columns;
    return QRect(column * getFrameWidth(), row * getFrameHeight(), getFrameWidth(),
                 getFrameHeight());
}

void Sprite::draw(QPainter& painter, const QRect& destination) {
    painter.drawPixmap(destination, source, getFrameBounds());
}

void Sprite::update(uint64_t timeDeltaMSec) {
    lastUpdateTime += timeDeltaMSec;
}

void Sprite::jump(int frameNumber) {
    lastUpdateTime = frameNumber * framesPerSec;
}

