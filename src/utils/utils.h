#ifndef UTILS_H
#define UTILS_H

#include <QPoint>
#include <QColor>
#include <QRect>
#include <QPolygon>

namespace client {

namespace display {
QRect getrect(QRect rect);

QPolygon getpolygon(QPolygon polygon);

QPolygonF getpolygon(QPolygonF polygon);

int getx(QPoint position, int x);

int gety(QPoint position, int y);
}

namespace utils {
int get_scaled_x(QPoint position, int x, double scale, int width);

int get_scaled_y(QPoint position, int y, double scale, int height);

int get_scaled(int x, double scale);
}

namespace geometry {
QPolygon regularPolygon(int size, int radius, QPoint position);
}

namespace colors {
const QColor interface_green = QColor(74, 192, 23);

const QColor interface_red = QColor(200, 192, 23);

const QColor simple = QColor(213, 227, 219);

const QColor corona = QColor(209, 48, 48);

const QColor wall = QColor(90, 90, 90);

}

}

#endif //UTILS_H
