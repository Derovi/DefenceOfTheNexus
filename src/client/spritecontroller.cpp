#include "spritecontroller.h"

const std::shared_ptr<core::Object>& SpriteController::getObject() const {
    return object;
}

SpriteController::SpriteController(const std::shared_ptr<core::Object>& object): object(object) {}

void SpriteController::update(QPainter painter, const QRect& target, uint64_t timeDeltaMSec) {
    onUpdate(timeDeltaMSec);
    for (auto sprite : sprites) {
        sprite->update(timeDeltaMSec);
        sprite->draw(painter, target);
    }
}

void SpriteController::addSprite(const std::shared_ptr<Sprite>& sprite) {
    sprites.push_back(sprite);
}

void SpriteController::removeSprite(const std::shared_ptr<Sprite>& sprite) {
    sprites.removeAll(sprite);
}
