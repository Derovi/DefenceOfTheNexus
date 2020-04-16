#include <memory>

#include <QDateTime>
#include <QPainter>
#include <QMainWindow>
#include <QDebug>
#include <QApplication>
#include <QMouseEvent>

#include "mainwindow.h"
#include "properties.h"
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
            setFixedWidth(properties::width);
            setFixedHeight(properties::height);
            update();
            lastFrame = currentTime;
            uiThread->msleep(1);
        }
    }));
    openScreen(std::shared_ptr<Screen>(new MenuScreen()));
    uiThread->start();
}

void client::MainWindow::mousePressEvent(QMouseEvent* event) {
    if (!screens.empty()) {
        screens.top()->click(event->pos());
    }
}

void client::MainWindow::draw() {
    if (!screens.empty()) {
        QPainter painter(this);
        screens.top()->draw(painter);
    }
}

std::shared_ptr<QThread> client::MainWindow::getUiThread() const {
    return uiThread;
}

void client::MainWindow::paintEvent(QPaintEvent*) {
    draw();
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

client::MainWindow* client::MainWindow::instance;
