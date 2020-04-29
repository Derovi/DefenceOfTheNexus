#ifndef SHORTESTPATHSTRATEGY_H
#define SHORTESTPATHSTRATEGY_H

#include <memory>

#include <QString>
#include <QStringList>

#include "../../core/object.h"
#include "../../core/attributes/moving.h"

#include "strategy.h"

namespace server {

class ShortestPathStrategy : public Strategy {
  public:
    static const QString name;

    explicit ShortestPathStrategy(std::shared_ptr<core::Object> object);

    ~ShortestPathStrategy() override = default;

    QString getName() override;

    void assign(DataBundle& dataBundle) override;

    void tick(std::shared_ptr<core::GameWorld> world, double timeDelta) override;

  private:
    static const QStringList requiredAttributes;
    static const QStringList startAfter;

    bool buildMap(std::shared_ptr<core::GameWorld> world, double cellSize);

    bool bfs();

    std::shared_ptr<core::Moving> moving;
    std::shared_ptr<QPointF> destPoint;
    QVector<QVector<char>> map;

};

}  // namespace server


#endif  // SHORTESTPATHSTRATEGY_H
