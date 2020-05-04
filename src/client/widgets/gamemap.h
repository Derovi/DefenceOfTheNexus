#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <QDateTime>
#include <QQueue>

#include "../../utils/queue.h"
#include "../../core/command.h"
#include "../../core/gameworld.h"
#include "../screen.h"
#include "../graphicsobject.h"
#include "../widget.h"

namespace client {

class GameMap : public Widget {
  public:
    GameMap(QPoint position = QPoint(0, 0), int height = 2160, int width = 3840);

    const QRect& getDisplayBounds() const;

    void setDisplayBounds(const QRect& displayBounds);

    const std::shared_ptr<core::GameWorld>& getGameWorld() const;

    void setGameWorld(const std::shared_ptr<core::GameWorld>& gameWorld);

    QTransform getTransformToWidget() const;

    QTransform getTransformToMap() const;

    void scaleWindow(double scaling);

    void centerWindow(const QPoint& point);

    QPoint getWindowCenter() const;

    void resizeWindow(const QPoint& size);

    QPoint getWindowSize() const;

    void changeWindowWidth(int width);

    int getWindowWidth() const;

    void changeWindowHeight(int width);

    int getWindowHeight() const;

    bool isShowHitBoxes() const;

    void setShowHitBoxes(bool showHitBoxesMode);

    bool isShowSprites() const;

    void setShowSprites(bool showSprites);

    const Sprite& getBackground() const;

    void setBackground(const Sprite& background);

    void setBackground(const QPixmap& background);

    const QHash<int64_t, std::shared_ptr<GraphicsObject>>& getGraphicsObjects() const;

  protected:
    void wheelEvent(QWheelEvent* event) override;

  protected:
    void paint(QPainter& painter) override;

    void clicked(QPoint point, bool leftButton) override;

  public:
    const std::shared_ptr<Queue<core::Command>>& getCommandQueue() const;

    void setCommandQueue(const std::shared_ptr<Queue<core::Command>>& commandQueue);

    bool isFixed() const;

    void setFixed(bool fixed);

  private:
    QRect displayBounds;

    std::shared_ptr<core::GameWorld> gameWorld;

    QHash<int64_t, std::shared_ptr<GraphicsObject>> graphicsObjects;

    std::shared_ptr<Queue<core::Command>> commandQueue;

    Sprite background;

    int cameraSpeed;

    bool showHitBoxes;

    bool showSprites;

    bool fixed;

    void drawBackground(QPainter& painter);
};

}

#endif  // GAMEMAP_H
