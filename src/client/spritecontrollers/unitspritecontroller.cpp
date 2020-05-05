#include <memory>

#include <QDebug>

#include "../../utils/factory.h"
#include "unitspritecontroller.h"
#include "../../core/attributes/moving.h"
#include "../../core/attributes/damaging.h"

void client::UnitSpriteController::onUpdate(uint64_t timeDeltaMSec) {
    clearSprites();
    if (getObject()->hasAttribute("damaging")) {
        auto damaging = std::dynamic_pointer_cast<core::Damaging>(getObject()->getAttribute("damaging"));
        if (damaging->isAttacking()) {
            double progress = 1 - static_cast<double>(damaging->getCurrentDelay()) / damaging->getAttackDelay();
            progress += 0.5;
            if (progress >= 1) {
                --progress;
            }
            attackSprite->jump(attackSprite->getFrameCount() * progress);
            addSprite(attackSprite);
            return;
        }
    }
    if (getObject()->hasAttribute("moving")) {
        auto moving = std::dynamic_pointer_cast<core::Moving>(getObject()->getAttribute("moving"));
        if (moving->getSpeed() > 0.01) {
            runSprite->setMirroring(moving->getDirection().x() < 0);
            idleSprite->setMirroring(moving->getDirection().x() < 0);
            addSprite(runSprite);
            return;
        }
    }
    addSprite(idleSprite);
}

client::UnitSpriteController::UnitSpriteController(const std::shared_ptr<core::Object>& object):
        SpriteController(object), runSprite(nullptr), idleSprite(nullptr), attackSprite(nullptr) {
    auto description = utils::Factory::getObjectGraphicsDescription(object->getTypeName());
    if (!description) {
        return;
    }
    const auto& spriteDescriptions = description->getSpriteDescriptions();
    if (spriteDescriptions.contains("idle")) {
        idleSprite = std::make_shared<Sprite>(description->getSpriteDescriptions()["idle"]);
    }
    if (spriteDescriptions.contains("run")) {
        runSprite = std::make_shared<Sprite>(description->getSpriteDescriptions()["run"]);
    }
    if (spriteDescriptions.contains("attack")) {
        attackSprite = std::make_shared<Sprite>(description->getSpriteDescriptions()["attack"]);
        attackSprite->setFramesPerSec(1);
    }
}

QString client::UnitSpriteController::getName() {
    return name;
}

QString client::UnitSpriteController::name = "unit";

const std::shared_ptr<client::Sprite>& client::UnitSpriteController::getRunSprite() const {
    return runSprite;
}

void client::UnitSpriteController::setRunSprite(const std::shared_ptr<Sprite>& runSprite) {
    UnitSpriteController::runSprite = runSprite;
}

const std::shared_ptr<client::Sprite>& client::UnitSpriteController::getIdleSprite() const {
    return idleSprite;
}

void client::UnitSpriteController::setIdleSprite(const std::shared_ptr<Sprite>& idleSprite) {
    UnitSpriteController::idleSprite = idleSprite;
}

const std::shared_ptr<client::Sprite>& client::UnitSpriteController::getAttackSprite() const {
    return attackSprite;
}

void client::UnitSpriteController::setAttackSprite(const std::shared_ptr<Sprite>& attackSprite) {
    UnitSpriteController::attackSprite = attackSprite;
}
