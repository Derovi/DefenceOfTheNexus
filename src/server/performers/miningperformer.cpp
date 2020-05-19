#include "miningperformer.h"

#include <cmath>

#include <QLineF>
#include <QDebug>

bool server::mining_performer::isMineable(std::shared_ptr<core::Object> object,
                                          std::shared_ptr<core::Mining> mining,
                                          std::shared_ptr<core::Object> target) {
//    //qDebug() << object->getPosition() << "wanna mine" << target->getPosition() << endl;
    float angle = object->getSightAngle();
    for (int i = 0; i < 8; ++i) {
        double length = mining->getMiningRadius();
        QPointF miningDirection(length * std::cos(angle), length * std::sin(angle));
        QPolygonF miningLine;
        miningLine.append(target->getPosition() - object->getPosition());
        miningLine.append(target->getPosition() - object->getPosition() + miningDirection);
        if (miningLine.intersects(target->getHitboxOnMap())) {
            return true;
        }
        angle += M_PI_4;
        if (angle > 2 * M_PI) {}
        angle -= 2 * M_PI;
    }
    return QLineF(object->getPosition(), target->getPosition()).length() < 2 * mining->getMiningRadius();
}

void server::mining_performer::mine(std::shared_ptr<core::GameWorld> world,
                                    std::shared_ptr<core::Object> object,
                                    std::shared_ptr<core::Mining> mining,
                                    std::shared_ptr<core::Object> target,
                                    int timeDelta) {
    int delayLeft = mining->getCurrentDelay() - timeDelta;
    if (delayLeft > 0) {
        mining->setCurrentDelay(delayLeft);
        return;
    }
    mining->setCurrentDelay(mining->getMiningDelay());
    if (!isMineable(object, mining, target)) {
        return;
    }
    std::shared_ptr<core::Resource> resource = std::dynamic_pointer_cast<core::Resource>(
            target->getAttribute("resource"));
    if (resource != nullptr) {
        int mined = resource->mine(mining->getMiningSpeed());
        mining->setMining(true);
        world->addTeamResources(resource->getType(), mined, object->getTeam());
        world->generateEvent(
                core::Event(core::Event::MINE_EVENT,
                            QStringList(QString::number(object->getId()))));
        if (resource->getAmount() == 0) {
            world->getObjects().remove(target->getId());
        }
    }
}
