#include "unispritecontroller.h"

void client::UniSpriteController::onUpdate(uint64_t timeDeltaMSec) {
    if (!getObject()->hasAttribute("moving")) {
        moveSprite->jump(0);
    }
}

client::UniSpriteController::UniSpriteController(const std::shared_ptr<core::Object>& object):
        SpriteController(object) {
    moveSprite = std::shared_ptr<Sprite>(new Sprite(QPixmap(":/sprites/unit1"),1,20));
    addSprite(moveSprite);
}

const std::shared_ptr<client::Sprite>& client::UniSpriteController::getMoveSprite() const {
    return moveSprite;
}

void client::UniSpriteController::setMoveSprite(const std::shared_ptr<Sprite>& moveSprite) {
    UniSpriteController::moveSprite = moveSprite;
}
