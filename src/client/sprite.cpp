#include "sprite.h"

client::Sprite::Sprite(const QPixmap& source, int rows, int columns, int framesPerSec):
        source(source), rows(rows), columns(columns), framesPerSec(framesPerSec),
        lastUpdateTime(0) {}

int client::Sprite::getRows() const {
    return rows;
}

int client::Sprite::getColumns() const {
    return columns;
}

int client::Sprite::getCurrentFrame() const {
    return lastUpdateTime / framesPerSec % getFrameCount();
}

int client::Sprite::getFrameCount() const {
    return rows * columns;
}

int client::Sprite::getFramesPerSec() const {
    return framesPerSec;
}

void client::Sprite::setFramesPerSec(int framesPerSec) {
    int currentFrame = getCurrentFrame();
    this->framesPerSec = framesPerSec;
    jump(currentFrame);
}

int client::Sprite::getFrameWidth() const {
    return source.width() / columns;
}

int client::Sprite::getFrameHeight() const {
    return source.height() / rows;
}

QRect client::Sprite::getFrameBounds() const {
    int row = getCurrentFrame() / columns;
    int column = getCurrentFrame() % columns;
    return QRect(column * getFrameWidth(), row * getFrameHeight(), getFrameWidth(),
                 getFrameHeight());
}

void client::Sprite::draw(QPainter& painter, const QRect& destination) {
    painter.drawPixmap(destination, source, getFrameBounds());
}

void client::Sprite::update(uint64_t timeDeltaMSec) {
    lastUpdateTime += timeDeltaMSec;
}

void client::Sprite::jump(int frameNumber) {
    lastUpdateTime = frameNumber * framesPerSec;
}

