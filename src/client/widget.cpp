#include <QPainter>
#include <QDebug>

#include "widget.h"
#include "windowmanager.h"
#include "mainwindow.h"

client::Widget::Widget(const QPoint& position): position(position) {

}

std::shared_ptr<client::Widget> client::Widget::getParent() {
    return parent;
}

int client::Widget::getHeght() {
    return height;
}


int client::Widget::getWidth() {
    return width;
}

void client::Widget::setParent(const std::shared_ptr<client::Widget>& parent) {
    this->parent = parent;
}

void client::Widget::addChild(client::Widget* child) {
    children.push_back(child);
    child->setParent(std::shared_ptr<Widget>(this));
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
    QPainter painter(MainWindow::getInstance());
    painter.translate(window_manager::get_real_x(absolutePosition().x()),
                      window_manager::get_real_y(absolutePosition().y()));
    painter.setTransform(QTransform(window_manager::getTransform()), true);
    paint(painter);
    for (Widget* interfacePart : children) {
        interfacePart->draw();
    }
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
    for (Widget* child : children) {
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

void client::Widget::click(QPoint point) {
    bool is_clicked = false;
    for (Widget* child : children) {
        if (child->isPointOnWidget(point)) {
            is_clicked = true;
            child->click(QPoint(point.x() - child->getPosition().x(),
                                point.y() - child->getPosition().y()));
        }
    }
    if (!is_clicked) {
        if (onClick != nullptr) {
            onClick(point);
        }
        clicked(point);
    }
}

void client::Widget::setOnClick(std::function<void(QPoint)> action) {
    this->onClick = action;
}

void client::Widget::wheel(QWheelEvent* event) {
    bool handled = false;
    for (Widget* child : children) {
        if (child->isPointOnWidget(event->pos() - absolutePosition())) {
            handled = true;
            child->wheel(event);
        }
    }
    if (!handled) {
        wheelEvent(event);
    }
}
