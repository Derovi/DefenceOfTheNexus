#include <QDebug>
#include <QRect>
#include <QtMath>

#include "utils.h"
#include "../client/windowmanager.h"

QRect client::display::getrect(QRect rect) {
    return QRect(window_manager::get_real_x(rect.x()), window_manager::get_real_y(rect.y()),
                 window_manager::get_real_x(rect.width()),
                 window_manager::get_real_y(rect.height()));
}

QPolygon client::display::getpolygon(QPolygon polygon) {
    for (QPoint& point : polygon) {
        point.setX(window_manager::get_real_x(point.x()));
        point.setY(window_manager::get_real_y(point.y()));
    }
    return polygon;
}

QPolygonF client::display::getpolygon(QPolygonF polygon) {
    for (QPointF& point : polygon) {
        point.setX(window_manager::get_real_x(point.x()));
        point.setY(window_manager::get_real_y(point.y()));
    }
    return polygon;
}

int client::display::getx(QPoint position, int x) {
    return window_manager::get_real_x(position.x() + x);
}

int client::display::gety(QPoint position, int y) {
    return window_manager::get_real_y(position.y() + y);
}

int client::utils::get_scaled(int x, double scale) {
    return static_cast<int>(x * scale);
}

int client::utils::get_scaled_x(QPoint position, int x, double scale, int width) {
    return position.x() + width / 2 +
           static_cast<int>((x - width / 2) * scale);
}

int client::utils::get_scaled_y(QPoint position, int y, double scale, int height) {
    return position.y() + height / 2 +
           static_cast<int>((y - height / 2) * scale);
}

QPolygon client::geometry::regularPolygon(int size, int radius, QPoint point) {
    QPolygon polygon;
    for (int idx = 0; idx < size; ++idx) {
        polygon << QPoint(point.x() + radius * qCos(2.0 * M_PI * idx / size), point.y() +
                                                                              radius *
                                                                              qSin(2.0 * M_PI *
                                                                                   idx / size));
    }
    return polygon;
}
