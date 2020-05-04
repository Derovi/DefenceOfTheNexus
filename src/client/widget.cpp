#include <QPainter>
#include <QDebug>

#include "widget.h"
#include "windowmanager.h"
#include "app.h"

client::Widget::Widget(const QPoint& position):
        position(position), windowManager(nullptr), width(0), height(0),
        lastPaintTime(QDateTime::currentDateTime()) {}

client::Widget* client::Widget::getParent() {
    return parent;
}

int client::Widget::getHeght() {
    return height;
}

client::Widget::~Widget() {
    qDebug() << "delete";
    for (Widget* child : children) {
        delete child;
    }
}

int client::Widget::getWidth() {
    return width;
}

void client::Widget::setParent(client::Widget* parent) {
    this->parent = parent;
}

void client::Widget::addChild(Widget* child) {
    children.push_back(child);
    child->setParent(this);
}

void client::Widget::setPosition(const QPoint& position) {
    this->position = position;
}

QPoint client::Widget::getPosition() {
    return position;
}

QPoint client::Widget::absolutePosition() {
    int x = position.x();
    int y = position.y();

    if (getParent() != nullptr) {
        x += getParent()->absolutePosition().x();
        y += getParent()->absolutePosition().y();
    }

    return QPoint(x, y);
}

void client::Widget::draw() {
    QPainter painter(App::getInstance());
    painter.translate(window_manager::get_real_x(absolutePosition().x()),
                      window_manager::get_real_y(absolutePosition().y()));
    painter.setTransform(QTransform(window_manager::getTransform()), true);
    paint(painter);
    for (const auto& interfacePart : children) {
        interfacePart->draw();
    }
    lastPaintTime = QDateTime::currentDateTime();
}

bool client::Widget::isPointOnWidget(const QPoint& point) {
    return point.x() >= position.x() &&
           point.y() >= position.y() &&
           point.x() <= position.x() + width &&
           point.y() <= position.y() + height;
}

void client::Widget::setHovered(bool hovered) {
    this->is_hovered = hovered;
}

bool client::Widget::isHovered() {
    return is_hovered;
}

void client::Widget::mouse(QPoint point) {
    is_hovered = true;
    mouseMoved(point);
    for (const auto& child : children) {
        if (child->isPointOnWidget(point)) {
            child->mouse(QPoint(point.x() - child->getPosition().x(),
                                point.y() - child->getPosition().y()));
        }
    }
}

bool client::Widget::isPointInBounds(const QPoint& point) {
    return point.x() >= position.x() + bound_width / 2 &&
           point.y() >= position.y() + bound_width / 2 &&
           point.x() <= position.x() + width - bound_width / 2 &&
           point.y() <= position.y() + height - bound_width / 2;
}

bool client::Widget::isPointOnBounds(const QPoint& point) {
    return isPointOnWidget(point) && !isPointInBounds(point);
}

QRect client::Widget::boundsRect() {
    return QRect(bound_width / 2,
                 bound_width / 2,
                 width - bound_width,
                 height - bound_width);
}

void client::Widget::click(QPoint point, bool leftButton) {
    bool is_clicked = false;

    for (int index = static_cast<int>(children.size()) - 1;
         index >= 0;
         --index) {
        if (!children[index]) {
            continue;
        }
        if (children[index]->isPointOnWidget(point)) {
            is_clicked = true;
            children[index]->click(QPoint(point.x() - children[index]->getPosition().x(),
                                          point.y() - children[index]->getPosition().y()),
                                                  leftButton);
            break;
        }
    }
    if (is_clicked) {
        return;
    }
    if (onClick != nullptr) {
        onClick(point, leftButton);
    }
    clicked(point, leftButton);
}

void client::Widget::setOnClick(std::function<void(QPoint, bool)> action) {
    this->onClick = action;
}

void client::Widget::wheel(QWheelEvent* event) {
    bool handled = false;
    for (const auto& child : children) {
        if (child->isPointOnWidget(event->pos() - absolutePosition())) {
            handled = true;
            child->wheel(event);
        }
    }
    if (!handled) {
        wheelEvent(event);
    }
}

void client::Widget::setHeight(int height) {
    Widget::height = height;
}

void client::Widget::setWidth(int width) {
    Widget::width = width;
}

const QDateTime& client::Widget::getLastPaintTime() const {
    return lastPaintTime;
}

int64_t client::Widget::getDeltaTime() const {
    return getLastPaintTime().msecsTo(QDateTime::currentDateTime());
}

void client::Widget::setLastPaintTime(const QDateTime& lastPaintTime) {
    Widget::lastPaintTime = lastPaintTime;
}
