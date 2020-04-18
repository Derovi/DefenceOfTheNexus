#include <memory>

#include "../../utils/factory.h"
#include "unitspritecontroller.h"
#include "../../core/attributes/moving.h"

void client::UnitSpriteController::onUpdate(uint64_t timeDeltaMSec) {
    if (!getObject()->hasAttribute("moving")) {
        if (moveSprite) {
            moveSprite->pause();
        }
    } else {
        auto moving = std::dynamic_pointer_cast<core::Moving>(getObject()->getAttribute("moving"));
        if (moving->getDirection().x() < 0) {
            if (moveSprite) {
                moveSprite->pause();
            }
        } else {
            if (moveSprite) {
                moveSprite->resume();
            }
        }
    }
}

client::UnitSpriteController::UnitSpriteController(const std::shared_ptr<core::Object>& object):
        SpriteController(object) {
    auto description = utils::Factory::getObjectGraphicsDescription(object->getTypeName());
    if (description != std::nullopt && description->getSpriteDescriptions().contains("moving")) {
        moveSprite = std::shared_ptr<Sprite>(
                new Sprite(description->getSpriteDescriptions()["moving"]));
        addSprite(moveSprite);
    }
}

const std::shared_ptr<client::Sprite>& client::UnitSpriteController::getMoveSprite() const {
    return moveSprite;
}

void client::UnitSpriteController::setMoveSprite(const std::shared_ptr<Sprite>& moveSprite) {
    UnitSpriteController::moveSprite = moveSprite;
}
