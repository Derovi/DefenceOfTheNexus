#include <QDateTime>
#include <QPainter>
#include <QMainWindow>
#include <QDebug>
#include <QApplication>
#include <QMouseEvent>

#include "mainwindow.h"
#include "windowmanager.h"
#include "properties.h"

client::MainWindow::MainWindow() {
    //showFullScreen();
    uiThread = std::shared_ptr<QThread>(QThread::create([&] {
        int64_t lastFrame;
        while (true) {
            if (uiThread == nullptr) {
                break;
            }
            int64_t currentTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
            if (lastFrame + 1000 / properties::frameRate > currentTime) {
                uiThread->msleep(1);
                continue;
            }
            setFixedWidth(properties::width);
            setFixedHeight(properties::height);
            update();
            lastFrame = currentTime;
            uiThread->msleep(1);
        }
    }));
    uiThread->start();
}

void client::MainWindow::mousePressEvent(QMouseEvent* event) {
    for (const std::shared_ptr<Widget>& widget : widgets) {
        if (widget->isPointOnWidget(QPoint(window_manager::get_x4k(event->x()),
                                           window_manager::get_y4k(event->y())))) {
            widget->click(QPoint(window_manager::get_x4k(event->x()) - widget->getPosition().x(),
                                 window_manager::get_y4k(event->y()) - widget->getPosition().y()));
        }
    }
}

void client::MainWindow::draw() {
    QPainter painter(this);
    for (std::shared_ptr<Widget> part : widgets) {
        part->draw(painter);
    }
}

std::shared_ptr<QThread> client::MainWindow::getUiThread() const {
    return uiThread;
}

void client::MainWindow::paintEvent(QPaintEvent*) {
    draw();
}
