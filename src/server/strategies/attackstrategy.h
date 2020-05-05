#ifndef ATTACKSTRATEGY_H
#define ATTACKSTRATEGY_H

#include "../../core/attributes/damaging.h"

#include "strategy.h"

namespace server {

class AttackStrategy : public Strategy {
  public:
    inline static const QString name = "attackStrategy";

    explicit AttackStrategy(std::shared_ptr<core::Object> object);

    ~AttackStrategy() override = default;

    void tick(std::shared_ptr<core::GameWorld> world, int timeDelta) override;

    QString getName() override;

    QStringList getRequiredAttributes() override;

    QStringList getStartAfter() override;

    void assign(DataBundle& dataBundle) override;

    void cancelTargets() override;

  private:
    inline static const QStringList requiredAttributes = {"damaging"};

    inline static const QStringList startAfter = {};

    std::shared_ptr<QPointF> destPoint;
    std::shared_ptr<core::Object> target;
    std::shared_ptr<core::Damaging> damaging;
};

}  // namespace server

#endif  // ATTACKSTRATEGY_H
