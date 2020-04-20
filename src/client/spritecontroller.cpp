#include "spritecontroller.h"

const std::shared_ptr<core::Object>& client::SpriteController::getObject() const {
    return object;
}

client::SpriteController::SpriteController(const std::shared_ptr<core::Object>& object): object(object) {}

void client::SpriteController::update(QPainter& painter, const QRect& target, uint64_t timeDeltaMSec) {
    onUpdate(timeDeltaMSec);
    for (auto sprite : sprites) {
        sprite->update(timeDeltaMSec);
        sprite->draw(painter, target);
    }
}

void client::SpriteController::addSprite(const std::shared_ptr<Sprite>& sprite) {
    sprites.push_back(sprite);
}

void client::SpriteController::removeSprite(const std::shared_ptr<Sprite>& sprite) {
    sprites.removeAll(sprite);
}
