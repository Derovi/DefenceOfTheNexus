#include "resourcespritecontroller.h"

#include "../../utils/factory.h"

client::ResourceSpriteController::ResourceSpriteController(
    const std::shared_ptr<core::Object>& object): SpriteController(object) {
    auto description = utils::Factory::getObjectGraphicsDescription(object->getTypeName());
    if (description != std::nullopt) {
        if (description->getSpriteDescriptions().contains("default")) {
            defaultSprite =
                std::make_shared<Sprite>(description->getSpriteDescriptions()["default"]);
            addSprite(defaultSprite);
        }
    }
}

void client::ResourceSpriteController::onUpdate(uint64_t timeDeltaMSec) {
}

QString client::ResourceSpriteController::getName() {
    return name;
}
