#include "minimap.h"
#include "../screens/gamescreen.h"

client::MiniMap::MiniMap(QPoint position, int height, int width): Widget(position) {
    setHeight(height);
    setWidth(width);
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
        if (abs(dx) > 800 || abs(dy) > 800) {
            continue;
        }
        QPolygonF drawPolygon = object->getRotatedHitbox();
        drawPolygon.translate(dx,dy);
        QTransform trans;
        trans=trans.scale(0.2,0.2);
        drawPolygon=trans.map(drawPolygon);
        drawPolygon.translate(position.x()+height/2,position.y()+width/2);
        if(object->getTeam()==0) {
            painter.setBrush(Qt::blue);
        }else{
            painter.setBrush(Qt::red);
        }
        painter.drawConvexPolygon(drawPolygon);

    }

}

void client::MiniMap::setGameWorld(const std::shared_ptr<core::GameWorld>& gameWorld) {
    MiniMap::gameWorld = gameWorld;
}
