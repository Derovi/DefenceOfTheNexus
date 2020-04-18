#include <QDebug>

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
    if (paused) {
        return;
    }
    if (isReverseDirection()) {
        lastUpdateTime -= timeDeltaMSec;
        if (lastUpdateTime < 0) {
            lastUpdateTime %= getAnimationDurationMSec();
            lastUpdateTime += getAnimationDurationMSec();
        }
    } else {
        lastUpdateTime += timeDeltaMSec;
    }
}

void client::Sprite::jump(int frameNumber) {
    lastUpdateTime = frameNumber * framesPerSec;
}

bool client::Sprite::isReverseDirection() const {
    return reverseDirection;
}

void client::Sprite::setReverseDirection(bool reverseDirection) {
    Sprite::reverseDirection = reverseDirection;
}

int64_t client::Sprite::getAnimationDurationMSec() {
    return getFrameCount() * 1000 / framesPerSec;
}

void client::Sprite::pause() {
    paused = true;
}

void client::Sprite::resume() {
    paused = false;
}

bool client::Sprite::isPaused() const {
    return paused;
}

const QPixmap& client::Sprite::getSource() const {
    return source;
}

client::Sprite::Sprite(const SpriteDescription& spriteDescription):
        source(QPixmap(spriteDescription.getResourceName())), rows(spriteDescription.getRows()),
        columns(spriteDescription.getColumns()) {}

