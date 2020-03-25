#include "gameconfiguration.h"

int GameConfiguration::getWidth() const {
    return width;
}

void GameConfiguration::setWidth(int width) {
    GameConfiguration::width = width;
}

int GameConfiguration::getHeight() const {
    return height;
}

void GameConfiguration::setHeight(int height) {
    GameConfiguration::height = height;
}

int GameConfiguration::getTickPerSec() const {
    return tickPerSec;
}

void GameConfiguration::setTickPerSec(int tickPerSec) {
    GameConfiguration::tickPerSec = tickPerSec;
}
