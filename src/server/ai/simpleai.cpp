#include "simpleai.h"

#include <random>

#include "../engine.h"
#include "../performers/movingperformer.h"
#include "../../utils/factory.h"

void server::SimpleAI::tick(int timeDelta) {
    loadBots(engine->getGameWorld());
    spawnBots(engine->getGameWorld());

    if (bots.empty()) {
        return;
    }

    //! TODO: compute probabilities
    for (Bot& bot : bots) {
        if (bot.targetId == ~0ull || !engine->getGameWorld()->getObjects().contains(bot.targetId)) {
            chooseTarget(bot);
        }

//        auto moving = std::dynamic_pointer_cast<core::Moving>(bot.object->getAttribute("moving"));
//
//        if (bot.isAggressive && moving_performer::isObstacles(bot.object, timeDelta,
//                                                              engine->getGameWorld(),
//                                                              std::dynamic_pointer_cast<core::Moving>(
//                                                                  bot.object->getAttribute("moving")))) {
//            QPolygonF objectPolygon = bot.object->getRotatedHitbox();
//            objectPolygon.translate(moving_performer::getNextPosition(bot.object, timeDelta, *moving));
//            for (const auto& otherObject : engine->getGameWorld()->getObjects()) {
//                if (otherObject->getId() == bot.object->getId()) {
//                    continue;
//                }
//                if (otherObject->isIntersect(objectPolygon)) {
//                    setTarget(bot, otherObject->getId());
//                    break;
//                }
//            }
//        }
    }
}

void server::SimpleAI::chooseTarget(server::SimpleAI::Bot& bot) {
    if (possibleTargets.empty()) {
        setTarget(bot, -1);
        return;
    }
    static std::mt19937_64 rnd(1337);
    std::uniform_int_distribution<> uprob(0, probSum);
    int64_t p = uprob(rnd);
    for (const auto& target : possibleTargets) {
        p -= target.second;
        if (p <= 0) {
            setTarget(bot, target.first);
            return;
        }
    }
    assert(false);
}

void server::SimpleAI::setTarget(server::SimpleAI::Bot& bot, uint64_t targetId) {
    bot.targetId = targetId;

    int botId = bot.object->getId();
    engine->getGameWorldController()->getControllers()[botId]->cancelTargets();

    if (targetId == ~0ull) {
        return;
    }

    auto target = engine->getGameWorld()->getObjects()[targetId];
    auto destPoint = std::make_shared<QPointF>(target->getPosition());

    DataBundle bundle;
    bundle.registerVariable("attackTarget", target);
    bundle.registerVariable("destinationPoint", destPoint);
    engine->getGameWorldController()->getControllers()[botId]->linkStrategies(bundle);
}

server::SimpleAI::Bot server::SimpleAI::makeBot(std::shared_ptr<core::Object> object) const {
    Bot bot;
    bot.isAggressive = true;
    bot.isDefender = false;
    bot.object = object;
    bot.targetId = -1;
    return bot;
}

void server::SimpleAI::loadBots(std::shared_ptr<core::GameWorld> world) {
    probSum = 0;
    possibleTargets.clear();
    for (const auto& object : engine->getGameWorld()->getObjects()) {
        if (object->getTeam() != team) {
            if (object->hasAttribute("damageable")) {
                possibleTargets.push_back({object->getId(), 1 + 3 * (object->getTypeName() == "nexus")});
                probSum += possibleTargets.back().second;
            }
            continue;
        }
        if (engine->getGameWorldController()->getControllers().contains(object->getId()) &&
            object->hasAttribute("damaging") && object->hasAttribute("moving")) {
            if (!bots.contains(object->getId())) {
                bots.insert(object->getId(), makeBot(object));
            }
        }
    }

    QVector<int> deadBots;
    for (const auto& bot : bots) {
        if (!engine->getGameWorld()->getObjects().contains(bot.object->getId())) {
            deadBots.push_back(bot.object->getId());
        }
    }

    for (int botId : deadBots) {
        bots.remove(botId);
    }
}

void server::SimpleAI::spawnBots(std::shared_ptr<core::GameWorld> world) {
    if (bots.empty()) {
        engine->getGameWorld()->summonObject(utils::Factory::getObjectSignature("scout").value(),
                                             QPoint(-200, 0), 0);
    }
}
