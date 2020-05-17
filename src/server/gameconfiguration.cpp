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

int GameConfiguration::getPlayerCount() const {
    return playerCount;
}

void GameConfiguration::setPlayerCount(int count) {
    playerCount = count;
}

double GameConfiguration::getResourceDensity() const {
    return resourceDensity;
}

void GameConfiguration::setResourceDensity(double density) {
    resourceDensity = density;
}

uint64_t GameConfiguration::getSeed() const {
    return seed;
}

void GameConfiguration::setSeed(uint64_t seed) {
    this->seed = seed;
}

QString GameConfiguration::getExplorerType() const {
    return explorerType;
}

void GameConfiguration::setExplorerType(QString explorer) {
    explorerType = explorer;
}
