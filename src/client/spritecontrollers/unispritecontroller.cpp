#include <memory>

#include "unispritecontroller.h"

void client::UniSpriteController::onUpdate(uint64_t timeDeltaMSec) {
    if (!getObject()->hasAttribute("moving")) {
        moveSprite->jump(0);
    }
}

client::UniSpriteController::UniSpriteController(const std::shared_ptr<core::Object>& object):
        SpriteController(object) {
    auto description = utils::Factory::getObjectGraphicsDescription(object->getTypeName());
    if (description->getSpriteNameToResource().contains("moving")) {
        moveSprite = std::shared_ptr<Sprite>(new Sprite(QPixmap(description->getSpriteNameToResource()["moving"]),1,20));
        addSprite(moveSprite);
    }
}

const std::shared_ptr<client::Sprite>& client::UniSpriteController::getMoveSprite() const {
    return moveSprite;
}

void client::UniSpriteController::setMoveSprite(const std::shared_ptr<Sprite>& moveSprite) {
    UniSpriteController::moveSprite = moveSprite;
}
