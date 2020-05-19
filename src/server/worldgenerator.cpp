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

    auto signatures = utils::Factory::getObjectSignatures();
    gameWorld->summonObject(utils::Factory::getObjectSignature("nexus").value(), QPoint(0, 0));

    for (int i = 0; i < config.getPlayerCount(); ++i) {
        int x = static_cast<int>(config.getWidth() / 3
            * std::cos(i * 2 * M_PI / config.getPlayerCount()));
        int y = static_cast<int>(config.getHeight() / 3
            * std::sin(i * 2 * M_PI / config.getPlayerCount()));
        gameWorld->summonObject(utils::Factory::getObjectSignature("nexus").value(),
                                QPoint(x, y),
                                i + 1);
        gameWorld->summonObject(
            utils::Factory::getObjectSignature(config.getExplorerType()).value(),
            QPoint(3000 + 200, 0),
            i + 1);
    }

    for (int y = -475; y <= 475; y += 200) {
        gameWorld->buildWall(QPoint(-500, y), QPoint(-500, y + 200),
                             utils::Factory::getObjectSignature("wall1").value(),
                             utils::Factory::getObjectSignature("column1").value());
        gameWorld->buildWall(QPoint(500, y), QPoint(500, y + 200),
                             utils::Factory::getObjectSignature("wall1").value(),
                             utils::Factory::getObjectSignature("column1").value());
    }
    for (int x = -475; x <= 475; x += 200) {
        if (x == -75) {
            continue;
        }
        gameWorld->buildWall(QPoint(x, -500), QPoint(x + 200, -500),
                             utils::Factory::getObjectSignature("wall1").value(),
                             utils::Factory::getObjectSignature("column1").value());
        gameWorld->buildWall(QPoint(x, 500), QPoint(x + 200, 500),
                             utils::Factory::getObjectSignature("wall1").value(),
                             utils::Factory::getObjectSignature("column1").value());
    }

    int d = 500;
    const int dx[] = {1, 1, -1, -1};
    const int dy[] = {1, -1, 1, -1};

    for (int i = 0; i < 4; ++i) {
        gameWorld->summonObject(utils::Factory::getObjectSignature("big-tower").value(),
                                QPoint(d * dx[i], d * dy[i]), 0);
    }

    d = 1200;
    for (int i = 0; i < 4; ++i) {
        gameWorld->summonObject(utils::Factory::getObjectSignature("medium-tower").value(),
                                QPoint(d * dx[i], d * dy[i]), 0);
    }

    d = 1000;
    for (int sign = -1; sign <= 1; sign += 2) {
        gameWorld->summonObject(utils::Factory::getObjectSignature("medium-barrack").value(),
                                QPoint(sign * d, 0), 0);
        gameWorld->summonObject(utils::Factory::getObjectSignature("medium-barrack").value(),
                                QPoint(0, sign * d), 0);
    }

    QHash<int, QVector<ObjectSignature>> resources;

    resources[static_cast<int>(core::ResourceType::kWood)] = {};
    resources[static_cast<int>(core::ResourceType::kStone)] = {};
    resources[static_cast<int>(core::ResourceType::kIron)] = {};

    for (auto& signature : signatures) {
        auto resourceAttribute = std::dynamic_pointer_cast<core::Resource>(
            signature.getAttribute("resource"));
        if (resourceAttribute != nullptr) {
            core::ResourceType resourceType = resourceAttribute->getType();
            resources[static_cast<int>(resourceType)].push_back(signature);
        }
    }

    int resourcesAmount = 1ll * config.getWidth() * config.getHeight()
        * config.getResourceDensity() * config.getResourceDensity();

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
    qDebug() << "World generated" << endl;

    return gameWorld;
}
