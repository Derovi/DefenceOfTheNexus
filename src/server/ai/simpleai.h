#ifndef SIMPLEAI_H
#define SIMPLEAI_H

#include <random>

#include <QHash>

#include "../../core/object.h"
#include "../../core/gameworld.h"
#include "../aiplayer.h"

namespace server {

class SimpleAI : public AIPlayer {
  public:
    SimpleAI(Engine* engine, int team): AIPlayer(engine, team) {}

    void tick(int timeDelta) override;

  private:
    struct Bot {
        bool isAggressive;
        bool isDefender;
        uint64_t targetId;
        std::shared_ptr<core::Object> object;
    };

    struct BotSpawner {
        uint64_t relatedObjectId;
        QPointF position;
        inline static QVector<QString> botTypes = {"scout", "pumpkin", "warrior", "ogre", "scorpion"};
    };

    void setTarget(Bot& bot, uint64_t targetId);

    void chooseTarget(Bot& bot);

    Bot makeBot(std::shared_ptr<core::Object> object) const;

    BotSpawner makeSpawner(std::shared_ptr<core::Object> object) const;

    void spawnBot(const BotSpawner& spanwer);

    void loadBots(std::shared_ptr<core::GameWorld> world);

    void spawnBots(std::shared_ptr<core::GameWorld> world);

    uint64_t probSum;
    std::mt19937_64 rnd{1337};
    QHash<uint64_t, Bot> bots;
    QHash<uint64_t, BotSpawner> spawners;
    QVector<QPair<uint64_t, uint64_t>> possibleTargets;
};

}  // namespace server

#endif  // SIMPLEAI_H
