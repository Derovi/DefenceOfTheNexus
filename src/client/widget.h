#ifndef WIDGET_H
#define WIDGET_H

#include <memory>
#include <functional>

#include <QObject>
#include <QPoint>
#include <QPainter>

namespace client {

class WindowManager;

class Widget : public QObject {
  public:
    Widget(const QPoint& position = QPoint(0,0));

    void setPosition(const QPoint& position);

    QPoint getPosition();

    QVector<Widget*> children;

    bool isPointOnWidget(const QPoint& point);

    bool isPointInBounds(const QPoint& point);

    bool isPointOnBounds(const QPoint& point);

    void setHovered(bool hovered);

    bool isHovered();

    void setOnClick(std::function<void(QPoint)> action);

    std::shared_ptr<Widget> getParent();

    void setParent(const std::shared_ptr<Widget>& parent);

    void addChild(Widget* child);

    QPoint absolutePosition();

    QRect boundsRect();

    int getHeght();

    int getWidth();

    WindowManager* windowManager;

  public slots:

    // called my main window
    void draw(QPainter& painter);

    void click(QPoint point);

    void mouse(QPoint point);

  protected:
    QPoint position;

    virtual void paint(QPainter& painter) {};

    virtual void clicked(QPoint point) {};

    virtual void mouseMoved(QPoint point) {};

    std::function<void(QPoint)> onClick;

    int height;
    int width;
    int bound_width = 0;

    bool is_hovered = false;

    std::shared_ptr<Widget> parent = nullptr;
};

}  // namespace client

#endif  // WIDGET_H
