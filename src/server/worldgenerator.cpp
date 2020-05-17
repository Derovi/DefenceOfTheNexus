#include "worldgenerator.h"

#include <cmath>
#include <random>

#include "../core/gameworld.h"
#include "../utils/factory.h"

std::shared_ptr<core::GameWorld> server::world_generator::generate(
    const GameConfiguration& config) {
    std::shared_ptr<core::GameWorld> gameWorld(new core::GameWorld());
    gameWorld->setHeight(config.getHeight());
    gameWorld->setWidth(config.getWidth());
    gameWorld->setTeamCount(config.getPlayerCount() + 1);

    // Enemy nexus
    gameWorld->summonObject(utils::Factory::getObjectSignature("nexus").value(), QPoint(0, 0));

    for (int i = 0; i < config.getPlayerCount(); ++i) {
        int x = static_cast<int>(20000 * std::cos(i * 2 * M_PI / config.getPlayerCount()));
        int y = static_cast<int>(20000 * std::sin(i * 2 * M_PI / config.getPlayerCount()));
        gameWorld->summonObject(utils::Factory::getObjectSignature("nexus").value(),
                                QPoint(x, y),
                                i + 1);
        gameWorld->summonObject(
            utils::Factory::getObjectSignature(config.getExplorerType()).value(),
            QPoint(x + 200, y),
            i + 1);

    }

    QHash<int, QVector<ObjectSignature>> resources;

    resources[static_cast<int>(core::ResourceType::kWood)] = {};
    resources[static_cast<int>(core::ResourceType::kStone)] = {};
    resources[static_cast<int>(core::ResourceType::kIron)] = {};

    for (const auto& type : {"conifer", "oak", "fir", "wite"}) {
        resources[static_cast<int>(core::ResourceType::kWood)].push_back(
            utils::Factory::getObjectSignature(type).value());
    }

    for (const auto& type : {"rock", "stone", "cobblestone", "small-stone", "medium-stone",
                             "big-stone"}) {
        resources[static_cast<int>(core::ResourceType::kStone)].push_back(
            utils::Factory::getObjectSignature(type).value());
    }

    for (const auto& type : {"iron", "ore"}) {
        resources[static_cast<int>(core::ResourceType::kIron)].push_back(
            utils::Factory::getObjectSignature(type).value());
    }

    int resourcesAmount = 1ll * config.getWidth() * config.getHeight()
        * config.getResourceDensity() * config.getResourceDensity();

    qDebug() << "Going to generate " << resourcesAmount << endl;

    float woodProb = 0.5;
    float stoneProb = 0.3;
    // ironProb = 0.2;

    std::mt19937 rnd(config.getSeed());
    std::uniform_int_distribution<> ux(-config.getWidth() / 2, config.getWidth() / 2);
    std::uniform_int_distribution<> uy(-config.getHeight() / 2, config.getHeight() / 2);
    std::uniform_real_distribution<> ur;

    const auto any = [&](const QVector<ObjectSignature>& signatures) {
        assert(!signatures.isEmpty());
        return signatures[rnd() % signatures.size()];
    };

    for (int i = 0; i < resourcesAmount; ++i) {
        qDebug() << "RES: " << i << endl;
        forever {
            int x = ux(rnd);
            int y = uy(rnd);
            float r = ur(rnd);
            ObjectSignature signature;
            if (r < woodProb) {
                signature = any(resources[static_cast<int>(core::ResourceType::kWood)]);
            } else if (r < woodProb + stoneProb) {
                signature = any(resources[static_cast<int>(core::ResourceType::kStone)]);
            } else {
                signature = any(resources[static_cast<int>(core::ResourceType::kIron)]);
            }
            if (gameWorld->summonObjectIfNoObstacles(signature, QPoint(x, y)) != nullptr) {
                break;
            }
        }
    }

    return gameWorld;
}
