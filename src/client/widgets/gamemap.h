#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "../widget.h"
#include "../../core/gameworld.h"

namespace client {

class GameMap : public Widget {
  public:
    GameMap(QPoint position = QPoint(0, 0), int height = 2160, int width = 3840);

    void setHeight(int height);

    void setWidth(int width);

    const QRect& getDisplayBounds() const;

    void setDisplayBounds(const QRect& displayBounds);

    const std::shared_ptr<core::GameWorld>& getGameWorld() const;

    void setGameWorld(const std::shared_ptr<core::GameWorld>& gameWorld);

    QPoint toWidgetPoint(const QPoint& mapPoint);

    QPoint toMapPoint(const QPoint& widgetPoint);

    QTransform getTransformToWidget() const;

    QTransform getTransformToMap() const;

  protected:
    void paint(QPainter& painter) override;

  private:
    QRect displayBounds;

    std::shared_ptr<core::GameWorld> gameWorld;
};

}

#endif //GAMEMAP_H
