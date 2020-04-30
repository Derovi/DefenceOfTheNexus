#include <QDebug>

#include "screen.h"
#include "mainwindow.h"
#include "windowmanager.h"

void client::Screen::pause() {
    if (state == PAUSED) {
        return;
    }
    state = PAUSED;
    onPaused();
}

void client::Screen::resume() {
    if (state == CURRENT) {
        return;
    }
    state = CURRENT;
    onResumed();
}

client::ScreenState client::Screen::getState() const {
    return state;
}

const client::Sprite& client::Screen::getBackground() const {
    return background;
}

void client::Screen::setBackground(const client::Sprite& background) {
    Screen::background = background;
}

void client::Screen::draw() {
    QPainter painter(MainWindow::getInstance());
    painter.translate(window_manager::get_real_x(absolutePosition().x()),
                      window_manager::get_real_y(absolutePosition().y()));
    painter.setTransform(QTransform(window_manager::getTransform()), true);
    if (!background.isNull()) {
        background.update(getDeltaTime());
        background.draw(painter, QRect(0,0,3840, 2160));
    }
    paint(painter);
    for (const auto& interfacePart : children) {
        interfacePart->draw();
    }
}
