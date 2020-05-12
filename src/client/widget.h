#ifndef WIDGET_H
#define WIDGET_H

#include <chrono>
#include <memory>
#include <functional>

#include <QObject>
#include <QPoint>
#include <QPainter>
#include <QtGui/QWheelEvent>
#include <QtCore/QDateTime>

namespace client {

class WindowManager;

class Widget : public QObject {
  public:
    explicit Widget(const QPoint& position = QPoint(0,0));

    virtual ~Widget();

    void setPosition(const QPoint& position);

    QPoint getPosition();

    QVector<Widget*> children;

    bool isPointOnWidget(const QPoint& point);

    bool isPointInBounds(const QPoint& point);

    bool isPointOnBounds(const QPoint& point);

    void setHovered(bool hovered);

    bool isHovered();

    void setOnClick(std::function<void(QPoint, bool)> action);

    Widget* getParent();

    void setParent(Widget* parent);

    void addChild(Widget* child);

    QPoint absolutePosition();

    QRect boundsRect();

    int getHeght();

    int getWidth();

    int getBoundsWidth() const;

    void setBoundsWidth(int boundsWidth);

    int64_t getDeltaTime() const;

    std::shared_ptr<WindowManager> windowManager;

    void setLastPaintTime(const std::chrono::steady_clock::time_point& lastPaintTime);

    virtual void paint(QPainter& painter) {};

  public slots:

    // called my main window
    virtual void draw();

    virtual void click(QPoint point, bool leftButton);

    virtual void mouse(QPoint point);

    virtual void wheel(QWheelEvent* event);

    virtual void setHeight(int height);

    virtual void setWidth(int width);

  protected:
    QPoint position;

    virtual void clicked(QPoint point, bool leftButton) {};

    virtual void mouseMoved(QPoint point) {};

    virtual void wheelEvent(QWheelEvent* event) {};

  public:
    const std::chrono::steady_clock::time_point& getLastPaintTime() const;

  protected:

    std::function<void(QPoint, bool)> onClick;

    int height;
    int width;
    int boundsWidth = 0;

    bool is_hovered = false;

    Widget* parent = nullptr;

    std::chrono::steady_clock::time_point lastPaintTime;
};

}  // namespace client

#endif  // WIDGET_H
