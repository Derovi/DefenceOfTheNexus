#include <memory>

#include <QDebug>

#include "../../utils/factory.h"
#include "defaultspritecontroller.h"
#include "../../core/attributes/moving.h"

void client::DefaultSpriteController::onUpdate(uint64_t timeDeltaMSec) {

}

client::DefaultSpriteController::DefaultSpriteController(
        const std::shared_ptr<core::Object>& object):
        SpriteController(object) {
    auto description = utils::Factory::getObjectGraphicsDescription(object->getTypeName());
    if (description != std::nullopt && description->getSpriteDescriptions().contains("default")) {
        defaultSprite = std::make_shared<Sprite>(
                *new Sprite(description->getSpriteDescriptions()["default"]));
        addSprite(defaultSprite);
    }
}

const std::shared_ptr<client::Sprite>& client::DefaultSpriteController::getDefaultSprite() const {
    return defaultSprite;
}

void client::DefaultSpriteController::setDefaultSprite(const std::shared_ptr<Sprite>& sprite) {
    DefaultSpriteController::defaultSprite = sprite;
}

QString client::DefaultSpriteController::getName() {
    return name;
}

QString client::DefaultSpriteController::name = "default";
