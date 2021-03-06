#ifndef PATHSTRATEGY_H
#define PATHSTRATEGY_H

#include <memory>

#include <QQueue>
#include <QString>

#include "../../core/attributes/moving.h"
#include "../../core/object.h"
#include "../../core/gameworld.h"
#include "../controllers/databundle.h"

#include "strategy.h"

namespace server {

class PathStrategy : public Strategy {
  public:
    explicit PathStrategy(std::shared_ptr<core::Object> object);

    ~PathStrategy() override = default;

    QString getName() override;

    void assign(DataBundle& dataBundle) override;

    void tick(std::shared_ptr<core::GameWorld> world, int timeDelta) override;

    void cancelTargets() override;

    inline static const QString name = "pathStrategy";

  private:
    inline static const QStringList requiredAttributes = {"moving"};
    inline static const QStringList startAfter = {};

    enum RoundingStyle {
        kClockwise,
        kCounterClockwise
    };

    bool isRounding;
    RoundingStyle roundingStyle;
    uint32_t destIntersectionUpdate;
    std::shared_ptr<core::Moving> moving;
    std::shared_ptr<QPointF> destPoint;
};

}  // namespace server


#endif  //PATHSTRATEGY_H
