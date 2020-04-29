#include "gameconfiguration.h"

int GameConfiguration::getWidth() const {
    return width;
}

void GameConfiguration::setWidth(int width) {
    this->width = width;
}

int GameConfiguration::getHeight() const {
    return height;
}

void GameConfiguration::setHeight(int height) {
    this->height = height;
}

int GameConfiguration::getTickPerSec() const {
    return tickPerSec;
}

void GameConfiguration::setTickPerSec(int tickPerSec) {
    this->tickPerSec = tickPerSec;
}
