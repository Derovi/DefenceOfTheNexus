#include "miningperformer.h"

#include <cmath>

#include <QLineF>
#include <QDebug>

bool server::mining_performer::isMineable(std::shared_ptr<core::Object> object,
                                          std::shared_ptr<core::Mining> mining,
                                          std::shared_ptr<core::Object> target) {
    float angle = object->getSightAngle();
    double length = mining->getMiningRadius();
    QPointF miningDirection(length * std::cos(angle), length * std::sin(angle));
    QPolygonF miningLine;
    miningLine.append(object->getPosition() - target->getPosition());
    miningLine.append(object->getPosition() + miningDirection - target->getPosition());
    return miningLine.intersects(target->getHitbox());
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
        for(int j=0;j<1000;j++)
            qDebug()<<"Roma";
        qDebug() << "Mined " << mined << " of " << (int) resource->getType() << endl;
        world->generateEvent(
                core::Event(core::Event::MINE_EVENT,
                            QStringList(QString::number(object->getId()))));
        if (resource->getAmount() == 0) {
            world->getObjects().remove(target->getId());
        }
    }
}
