#ifndef BULLETSTRATEGY_H
#define BULLETSTRATEGY_H

#include "../../core/attributes/bullet.h"
#include "../../core/attributes/moving.h"

#include "strategy.h"

namespace server {

class BulletStrategy : public Strategy {
  public:
    inline static const QString name = "bulletStrategy";

    explicit BulletStrategy(std::shared_ptr<core::Object> object);

    ~BulletStrategy() override = default;

    void tick(std::shared_ptr<core::GameWorld> world, int timeDelta) override;

    QString getName() override;

    QStringList getRequiredAttributes() override;

    QStringList getStartAfter() override;

    void assign(DataBundle& dataBundle) override;

    void cancelTargets() override;

  private:
    inline static const QStringList requiredAttributes = {"moving"};

    inline static const QStringList startAfter = {};

    std::shared_ptr<core::Bullet> bullet;
    std::shared_ptr<core::Moving> moving;
};

}  // namespace server

#endif  // BULLETSTRATEGY_H
