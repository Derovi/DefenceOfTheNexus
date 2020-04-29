#include "shortestpathstrategy.h"

#include <cmath>

#include <QVector2D>
#include <QLineF>

namespace server {

const int kMaxCells = 1000;

ShortestPathStrategy::ShortestPathStrategy(std::shared_ptr<core::Object> object):
        Strategy(object), moving(nullptr), destPoint(nullptr) {}

QString ShortestPathStrategy::getName() {
    return name;
}

void ShortestPathStrategy::assign(DataBundle& dataBundle) {
    dataBundle.assign("moving", moving);
    dataBundle.assign("destinationPoint", destPoint);
}

void ShortestPathStrategy::tick(std::shared_ptr<core::GameWorld> world, double timeDelta) {
    if (qFuzzyIsNull(moving->getSpeed()) || destPoint == nullptr) {
        moving->setDirection(QVector2D(0, 0));
        return;
    }
    if (!buildMap(world, moving->getSpeed() / 2) || !bfs()) {
        moving->setDirection(QVector2D(*destPoint - getObject()->getPosition()));
        return;
    }
}

bool ShortestPathStrategy::buildMap(std::shared_ptr<core::GameWorld> world, double cellSize) {
    const auto& departure = getObject()->getPosition();
    const auto& destination = *destPoint;
    int width = 2 * std::abs(std::ceil((departure.x() - destination.x()) / cellSize));
    int height = 2 * std::abs(std::ceil((departure.y() - destination.y()) / cellSize));
    if (1ll * height * width > kMaxCells) {
        return false;
    }
    map.resize(height);
    for (int i = 0; i < height; ++i) {
        map[i].resize(width);
        for (int j = 0; j < width; ++j) {
//            map[i][j] = isBusy();
        }
    }

}

bool ShortestPathStrategy::bfs() {
    return false;
}

const QString ShortestPathStrategy::name = "shortestPathStrategy";

}  // namespace server
