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
            runOnUiThread([&] {
                if (properties::fullscreen) {
                    showFullScreen();
                } else {
                    showNormal();
                    setFixedWidth(properties::width);
                    setFixedHeight(properties::height);
                }
                update();
            });
            lastFrame = currentTime;
            uiThread->msleep(1);
        }
    }));
    openScreen(std::shared_ptr<Screen>(new MenuScreen()));
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

std::shared_ptr<QThread> client::MainWindow::getUiThread() const {
    return uiThread;
}

void client::MainWindow::paintEvent(QPaintEvent*) {
    draw();
}

void client::MainWindow::runOnUiThread(std::function<void()> callback) {
    QTimer* timer = new QTimer();
    timer->moveToThread(qApp->thread());
    timer->setSingleShot(true);
    QObject::connect(timer, &QTimer::timeout, [=]() {
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
