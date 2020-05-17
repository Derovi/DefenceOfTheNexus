#ifndef TOWERSTRATEGY_H
#define TOWERSTRATEGY_H

#include "../../core/attributes/damaging.h"

#include "strategy.h"

namespace server {

class TowerStrategy : public Strategy {
  public:
    explicit TowerStrategy(std::shared_ptr<core::Object> object);

    ~TowerStrategy() override = default;

    QString getName() override;

    void assign(DataBundle& dataBundle) override;

    void tick(std::shared_ptr<core::GameWorld> world, int timeDelta) override;

    void cancelTargets() override;

    inline static const QString name = "towerStrategy";

  private:
    inline static const QStringList requiredAttributes = {"damaging"};
    inline static const QStringList startAfter = {};

    void chooseTarget(std::shared_ptr<core::GameWorld> world);

    uint64_t targetId;
    std::shared_ptr<core::Object> target;
    std::shared_ptr<core::Damaging> damaging;
};

}  // namespace server

#endif  // TOWERSTRATEGY_H
