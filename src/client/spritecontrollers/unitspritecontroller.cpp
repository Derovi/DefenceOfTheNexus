#include <memory>

#include <QDebug>

#include "../../utils/factory.h"
#include "unitspritecontroller.h"
#include "../../core/attributes/moving.h"

void client::UnitSpriteController::onUpdate(uint64_t timeDeltaMSec) {
    if (!getObject()->hasAttribute("moving")) {
        moveSprite->setFirstFrame(1);
        moveSprite->setLastFrame(1);
    } else {
        auto moving = std::dynamic_pointer_cast<core::Moving>(getObject()->getAttribute("moving"));
        moveSprite->setMirroring(moving->getDirection().x() < 0);
    }
}

client::UnitSpriteController::UnitSpriteController(const std::shared_ptr<core::Object>& object):
        SpriteController(object), moveSprite(nullptr), standSprite(nullptr), attackSprite(nullptr) {
    auto description = utils::Factory::getObjectGraphicsDescription(object->getTypeName());
    if (description == std::nullopt) {
        return;
    }
    const auto& spriteDescriptions = description->getSpriteDescriptions();
    if (spriteDescriptions.contains("moving")) {
        moveSprite = std::make_shared<Sprite>(description->getSpriteDescriptions()["moving"]);
        addSprite(moveSprite);
    }
    if (spriteDescriptions.contains("attack")) {
        attackSprite = std::make_shared<Sprite>(description->getSpriteDescriptions()["attack"]);
    }
}

std::shared_ptr<client::Sprite> client::UnitSpriteController::getMoveSprite() const {
    return moveSprite;
}

std::shared_ptr<client::Sprite> client::UnitSpriteController::getStandSprite() const {
    return standSprite;
}

std::shared_ptr<client::Sprite> client::UnitSpriteController::getAttackSprite() const {
    return attackSprite;
}

void client::UnitSpriteController::setMoveSprite(const std::shared_ptr<Sprite>& moveSprite) {
    UnitSpriteController::moveSprite = moveSprite;
}

void client::UnitSpriteController::setStandSprite(const std::shared_ptr<Sprite>& standSprite) {
    this->standSprite = standSprite;
}

void client::UnitSpriteController::setAttackSprite(const std::shared_ptr<Sprite>& attackSprite) {
    this->attackSprite = attackSprite;
}

QString client::UnitSpriteController::getName() {
    return name;
}

QString client::UnitSpriteController::name = "unit";
