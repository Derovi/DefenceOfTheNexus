#ifndef MINESTRATEGY_H
#define MINESTRATEGY_H

#include "../controllers/databundle.h"
#include "../../core/attributes/mining.h"
#include "strategy.h"

namespace server {

class MineStrategy : public Strategy {
  public:
    inline static const QString name = "mineStrategy";

    explicit MineStrategy(std::shared_ptr<core::Object> object);

    ~MineStrategy() override = default;

    void tick(std::shared_ptr<core::GameWorld> world, int timeDelta) override;

    QString getName() override;

    QStringList getRequiredAttributes() override;

    QStringList getStartAfter() override;

    void assign(DataBundle& dataBundle) override;

    void cancelTargets() override;

  private:
    inline static const QStringList requiredAttributes = {"mining"};

    inline static const QStringList startAfter = {};

    std::shared_ptr<core::Object> miningTarget;
    std::shared_ptr<core::Mining> mining;
};

}  // namespace server


#endif // MINESTRATEGY_H
