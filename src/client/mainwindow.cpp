#include <memory>

#include <QDateTime>
#include <QMetaObject>
#include <QTimer>
#include <QPainter>
#include <QMatrix>
#include <QMainWindow>
#include <QDebug>
#include <QApplication>
#include <QMouseEvent>

#include "mainwindow.h"
#include "properties.h"
#include "windowmanager.h"
#include "screens/menuscreen.h"

client::MainWindow::MainWindow() {
    //showFullScreen();
    instance = this;
    uiThread = QThread::create([&] {
        // time when last tick execution was started
        QDateTime lastTickStartTime = QDateTime::currentDateTime();
        while (true) {
            if (uiThread == nullptr) {
                break;
            }
            QDateTime currentTickStartTime = QDateTime::currentDateTime();
            // make changes on game world
            runOnUiThread([&] {
                if (properties::fullscreen) {
                    showFullScreen();
                } else {
                    showNormal();
                    setFixedWidth(properties::width);
                    setFixedHeight(properties::height);
                }
                hover(QPoint(window_manager::get_x4k(mapFromGlobal(cursor().pos()).x()),
                        window_manager::get_y4k(mapFromGlobal(cursor().pos()).y())));
                update();
            });

            // sleep until next tick
            QThread::msleep(1000 / properties::frameRate -
                            currentTickStartTime.msecsTo(QDateTime::currentDateTime()));
            lastTickStartTime = currentTickStartTime;
        }
    });
    openScreen(std::make_shared<MenuScreen>());
    uiThread->start();
}

void client::MainWindow::mousePressEvent(QMouseEvent* event) {
    if (!screens.empty()) {
        screens.top()->click(QPoint(window_manager::get_x4k(event->pos().x()),
                window_manager::get_y4k(event->pos().y())));
    }
}

void client::MainWindow::draw() {
    if (!screens.empty()) {
        QPainter painter(this);
        screens.top()->draw();
    }
}

QThread* client::MainWindow::getUiThread() const {
    return uiThread;
}

void client::MainWindow::paintEvent(QPaintEvent*) {
    draw();
}

void client::MainWindow::runOnUiThread(std::function<void()> callback) {
    QTimer* timer = new QTimer();
    timer->moveToThread(qApp->thread());
    timer->setSingleShot(true);
    connect(timer, &QTimer::timeout, [=]() {
        callback();
        timer->deleteLater();
    });
    QMetaObject::invokeMethod(timer, "start", Qt::QueuedConnection, Q_ARG(int, 0));
}

void client::MainWindow::openScreen(const std::shared_ptr<Screen>& screen) {
    if (!screens.empty()) {
        screens.top()->pause();
    }
    screens.push(screen);
}

void client::MainWindow::closeScreen() {
    if (screens.empty()) {
        return;
    }
    screens.pop();
    if (screens.empty()) {
        return;
    }
    screens.top()->resume();
}

client::MainWindow* client::MainWindow::getInstance() {
    return instance;
}

client::MainWindow* client::MainWindow::instance = nullptr;

void client::MainWindow::wheelEvent(QWheelEvent* event) {
    screens.top()->wheel(event);
}

void client::MainWindow::hover(QPoint point) {
    if (screens.empty()) {
        return;
    }

    Widget* current = screens.top().get();

    removeHovered(current);

    while (!current->children.empty()) {
        bool found = false;
        for (Widget* child : current->children) {
            if (child->isPointOnWidget(point)) {
                current = child;
                found = true;
            }
        }
        if (!found) {
            break;
        }
        point -= current->getPosition();
    }

    current->setHovered(true);
}

void client::MainWindow::removeHovered(client::Widget* widget) {
    widget->setHovered(false);
    for (Widget* child : widget->children) {
        removeHovered(child);
    }
}
