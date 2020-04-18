#include <memory>

#include "../../utils/factory.h"
#include "unispritecontroller.h"
#include "../../core/attributes/moving.h"

void client::UniSpriteController::onUpdate(uint64_t timeDeltaMSec) {
    if (!getObject()->hasAttribute("moving")) {
        moveSprite->pause();
    } else {
        auto moving = std::dynamic_pointer_cast<core::Moving>(getObject()->getAttribute("moving"));
        if (moving->getDirection().x() < 0) {
            moveSprite->pause();
        } else {
            moveSprite->resume();
        }
    }
}

client::UniSpriteController::UniSpriteController(const std::shared_ptr<core::Object>& object):
        SpriteController(object) {
    auto description = utils::Factory::getObjectGraphicsDescription(object->getTypeName());
    if (description->getSpriteNameToResource().contains("moving")) {
        moveSprite = std::shared_ptr<Sprite>(new Sprite(QPixmap(description->getSpriteNameToResource()["moving"])));
        addSprite(moveSprite);
    }
}

const std::shared_ptr<client::Sprite>& client::UniSpriteController::getMoveSprite() const {
    return moveSprite;
}

void client::UniSpriteController::setMoveSprite(const std::shared_ptr<Sprite>& moveSprite) {
    UniSpriteController::moveSprite = moveSprite;
}
