#include "miningperformer.h"

#include <cmath>

#include <QLineF>

void server::mining_performer::mine(std::shared_ptr<core::GameWorld> world,
                                    std::shared_ptr<core::Object> object,
                                    std::shared_ptr<core::Mining> mining, int timeDelta) {
    int delayLeft = mining->getCurrentDelay() - timeDelta;
    if (delayLeft > 0) {
        mining->setCurrentDelay(delayLeft);
        return;
    }
    mining->setCurrentDelay(mining->getMiningDelay());
    float angle = object->getRotationAngle();
    double length = mining->getMiningRadius();
    QPointF miningDirection(length * std::cos(angle), length * std::sin(angle));
    //! TODO: could be optimized
    //! TODO: fix multiple miningLine creation
    for (auto target : world->getObjects()) {
        QPolygonF miningLine;
        miningLine.append(object->getPosition() - target->getPosition());
        miningLine.append(object->getPosition() + miningDirection - target->getPosition());
        if (target == object || !miningLine.intersects(target->getHitbox())) {
            continue;
        }
        std::shared_ptr<core::Resource> resource = std::dynamic_pointer_cast<core::Resource>(
                target->getAttribute("resource"));
        if (resource != nullptr) {
            int mined = resource->mine(mining->getMiningSpeed());
            world->addResources(resource->getType(), mined);
            if (resource->getAmount() == 0) {
                world->getObjects().remove(target->getId());
            }
        }
    }
}
