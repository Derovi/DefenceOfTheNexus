#ifndef MINIMAP_H
#define MINIMAP_H

#include <functional>
#include <QImage>
#include <QDebug>

#include "../widget.h"
#include "textview.h"
#include "gamemap.h"

namespace client {
class GameScreen;

class MiniMap : public Widget {
  public:
    MiniMap(QPoint position, int height,
            int width);

    void paint(QPainter& painter) override;

    void setGameWorld(const std::shared_ptr<core::GameWorld>& gameWorld);

  private:

    std::shared_ptr<core::GameWorld> gameWorld;

};

} // namespace client
#endif //MINIMAP_H
