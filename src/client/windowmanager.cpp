#include <QTimer>
#include <QDebug>
#include <QMetaObject>

#include "mainwindow.h"
#include "windowmanager.h"
#include "properties.h"

QTransform client::window_manager::getTransform() {
    return QTransform(static_cast<double>(MainWindow::getInstance()->width()) / width4k, 0, 0,
                      static_cast<double>(MainWindow::getInstance()->height()) / height4k,0,0);
}

int client::window_manager::get_real_x(int x4k) {
    return x4k * MainWindow::getInstance()->width() / width4k;
}

int client::window_manager::get_real_y(int y4k) {
    return y4k * MainWindow::getInstance()->height() / height4k;
}

int client::window_manager::get_x4k(int x) {
    return x * width4k / MainWindow::getInstance()->width();
}

int client::window_manager::get_y4k(int y) {
    return y * height4k / MainWindow::getInstance()->height();
}
