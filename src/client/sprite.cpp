#include <QDebug>

#include "sprite.h"

client::Sprite::Sprite(const QPixmap& source, int rows, int columns, int framesPerSec):
        source(source), rows(rows), columns(columns), framesPerSec(framesPerSec),
        lastUpdateTime(0), paused(false), reverseDirection(false), mirroring(false), firstFrame(0),
        lastFrame(rows * columns - 1), backAndForthMode(false) {}

int client::Sprite::getRows() const {
    return rows;
}

int client::Sprite::getColumns() const {
    return columns;
}

int client::Sprite::getCurrentFrame() const {
    return lastUpdateTime * framesPerSec / 1000 % getFrameCount() + getFirstFrame();
}

int client::Sprite::getFrameCount() const {
    return getLastFrame() - getFirstFrame() + 1;
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
    if (source.isNull()) {
        return;
    }
    QRect dest = destination;
    QTransform transform = QTransform(-1, 0, 0, 1, 0, 0);
    if (mirroring) {
        painter.setTransform(transform, true);
        dest = transform.mapRect(dest);
    }
    painter.drawPixmap(dest, source, getFrameBounds());
    if (mirroring) {
        painter.setTransform(transform.inverted());
    }
}

uint64_t client::Sprite::getLastUpdateTime() const {
    return lastUpdateTime;
}

void client::Sprite::update(uint64_t timeDeltaMSec) {
    if (paused) {
        return;
    }
    int frameBeforeUpdate = getCurrentFrame();
    if (isReverseDirection()) {
        lastUpdateTime -= timeDeltaMSec;
        if (lastUpdateTime < 0) {
            lastUpdateTime %= getAnimationDurationMSec();
            lastUpdateTime += getAnimationDurationMSec();
        }
    } else {
        lastUpdateTime += timeDeltaMSec;
    }
    int frameAfterUpdate = getCurrentFrame();
    if (!backAndForthMode || frameBeforeUpdate == frameAfterUpdate) {
        return;
    }
    if (frameAfterUpdate == firstFrame) {
        reverseDirection = true;
        lastUpdateTime -= timeDeltaMSec;
    } else if (frameAfterUpdate == lastFrame) {
        reverseDirection = false;
        lastUpdateTime += timeDeltaMSec;
    }
}

void client::Sprite::jump(int frameNumber) {
    lastUpdateTime = frameNumber * 1000 / framesPerSec;
}

bool client::Sprite::isReverseDirection() const {
    return reverseDirection;
}

void client::Sprite::setReverseDirection(bool reverseDirection) {
    Sprite::reverseDirection = reverseDirection;
}

int64_t client::Sprite::getAnimationDurationMSec() const {
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

client::Sprite::Sprite(const SpriteDescription& spriteDescription): Sprite(
        QPixmap(spriteDescription.getResourceName()), spriteDescription.getRows(),
        spriteDescription.getColumns()) {}

bool client::Sprite::isMirroring() const {
    return mirroring;
}

void client::Sprite::setMirroring(bool mirroring) {
    Sprite::mirroring = mirroring;
}

int client::Sprite::getFirstFrame() const {
    return firstFrame;
}

void client::Sprite::setFirstFrame(int firstFrame) {
    Sprite::firstFrame = firstFrame;
}

int client::Sprite::getLastFrame() const {
    return lastFrame;
}

void client::Sprite::setLastFrame(int lastFrame) {
    Sprite::lastFrame = lastFrame;
}

bool client::Sprite::isBackAndForthMode() const {
    return backAndForthMode;
}

void client::Sprite::setBackAndForthMode(bool backAndForthMode) {
    Sprite::backAndForthMode = backAndForthMode;
}

bool client::Sprite::isNull() {
    return rows == 0;
}

