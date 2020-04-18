#include "uni1spritecontroller.h"

void client::Uni1SpriteController::onUpdate(uint64_t timeDeltaMSec) {

}

client::Uni1SpriteController::Uni1SpriteController(const std::shared_ptr<core::Object>& object):
        SpriteController(object) {
    moveSprite = std::shared_ptr<Sprite>(new Sprite(QPixmap(":/sprites/unit1"),1,20));
    addSprite(moveSprite);
}
