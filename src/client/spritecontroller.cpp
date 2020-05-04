#include "spritecontroller.h"

const std::shared_ptr<core::Object>& client::SpriteController::getObject() const {
    return object;
}

client::SpriteController::SpriteController(const std::shared_ptr<core::Object>& object): object(object) {}

void client::SpriteController::update(uint64_t timeDeltaMSec) {
    onUpdate(timeDeltaMSec);
    for (auto sprite : sprites) {
        sprite->update(timeDeltaMSec);
    }
}

void client::SpriteController::addSprite(const std::shared_ptr<Sprite>& sprite) {
    sprites.push_back(sprite);
}

void client::SpriteController::removeSprite(const std::shared_ptr<Sprite>& sprite) {
    sprites.removeAll(sprite);
}

void client::SpriteController::draw(QPainter& painter, const QRect& target) {
    for (auto sprite : sprites) {
        sprite->draw(painter, target);
    }
}
