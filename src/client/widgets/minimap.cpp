#include "minimap.h"
#include "../screens/gamescreen.h"

client::MiniMap::MiniMap(QPoint position, int height, int width): Widget(position) {
    setHeight(height);
    setWidth(width);
    brushes.push_back(Qt::blue);
    brushes.push_back(Qt::red);
    brushes.push_back(Qt::blue);
    brushes.push_back(Qt::black);
    brushes.push_back(Qt::yellow);
    brushes.push_back(Qt::green);
    brushes.push_back(Qt::magenta);
    brushes.push_back(Qt::cyan);
}

void client::MiniMap::paint(QPainter& painter) {
    QPoint cord = dynamic_cast<GameScreen*>(getParent()->getParent())
            ->getGameMap()->getWindowCenter();
    painter.setBrush(Qt::lightGray);
    painter.setPen(Qt::black);
    painter.drawRect(position.x(), position.y(), width, height);
    gameWorld = dynamic_cast<GameScreen*>(getParent()->getParent())->getGameMap()->getGameWorld();
    for (const auto& object: gameWorld->getObjects()) {
        double dx = object->getPosition().x() - cord.x();
        double dy = object->getPosition().y() - cord.y();
        if (abs(dx) > 750 || abs(dy) > 750) {
            continue;
        }
        QPolygonF drawPolygon = object->getRotatedHitbox();
        drawPolygon.translate(dx,dy);
        QTransform trans;
        trans=trans.scale(0.2,0.2);
        drawPolygon=trans.map(drawPolygon);
        drawPolygon.translate(position.x()+height/2,position.y()+width/2);
        painter.setBrush(brushes[object->getTeam()]);
        painter.drawConvexPolygon(drawPolygon);

    }

}

void client::MiniMap::setGameWorld(const std::shared_ptr<core::GameWorld>& gameWorld) {
    MiniMap::gameWorld = gameWorld;
}
