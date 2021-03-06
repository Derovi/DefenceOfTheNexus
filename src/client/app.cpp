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
#include <QtGui/QFontDatabase>

#include "../utils/serializer.h"
#include "../utils/lang.h"

#include "app.h"
#include "properties.h"
#include "windowmanager.h"
#include "screens/menuscreen.h"

client::App::App() {
    settings = std::make_shared<QSettings>("DOTN", "Defence Of the Nexus");
    if (settings->contains("properties")) {
        properties::load(utils::Serializer().stringToJsonObject(
                settings->value("properties").toString()).value());
    }

    utils::Lang::load(client::properties::lang, client::properties::baseLang);

    int fontId = QFontDatabase::addApplicationFont(":/fonts/pacifico");
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    font = QFont(fontFamily);
    font.setPixelSize(100);

    instance = this;
    uiThread = QThread::create([&] {
        // time when last tick execution was started
        auto lastTickStartTime = std::chrono::steady_clock::now();
        while (true) {
            if (uiThread == nullptr) {
                break;
            }
            auto currentTickStartTime = std::chrono::steady_clock::now();
            // make changes on game world
            runOnUiThread([&] {
                if (properties::fullscreen) {
                    if (!isFullScreen()) {
                        showFullScreen();
                    }
                } else {
                    if (isFullScreen()) {
                        showNormal();
                    }
                    setFixedWidth(properties::width);
                    setFixedHeight(properties::height);
                }
                hover(QPoint(window_manager::get_x4k(mapFromGlobal(cursor().pos()).x()),
                             window_manager::get_y4k(mapFromGlobal(cursor().pos()).y())));
                update();
            });

            // sleep until next tick
            int sleepTime = 1000 / properties::frameRate -
                std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::steady_clock::now() - currentTickStartTime).count();
            if (sleepTime > 0) {
                QThread::msleep(sleepTime);
            }
        }
    });
    openScreen(std::make_shared<MenuScreen>());
    uiThread->start();
}

void client::App::mousePressEvent(QMouseEvent* event) {
    if (!screens.empty()) {
        screens.top()->click(QPoint(window_manager::get_x4k(event->pos().x()),
                                    window_manager::get_y4k(event->pos().y())),
                                            event->button() == Qt::LeftButton);
    }
}

void client::App::keyPressEvent(QKeyEvent* event) {
    if (!screens.empty()) {
        screens.top()->keyPress(event);
    }
}

void client::App::draw() {
    if (!screens.empty()) {
        QPainter painter(this);
        screens.top()->draw();
    }
}

QThread* client::App::getUiThread() const {
    return uiThread;
}

void client::App::paintEvent(QPaintEvent*) {
    draw();
}

client::App::~App() {
    settings->setValue("properties",
                          utils::Serializer().jsonObjectToString(properties::serialize()));
    settings->sync();
}

void client::App::runOnUiThread(std::function<void()> callback) {
    QTimer* timer = new QTimer();
    timer->moveToThread(qApp->thread());
    timer->setSingleShot(true);
    connect(timer, &QTimer::timeout, [=]() {
        callback();
        timer->deleteLater();
    });
    QMetaObject::invokeMethod(timer, "start", Qt::QueuedConnection, Q_ARG(int, 0));
}

void client::App::openScreen(const std::shared_ptr<Screen>& screen) {
    if (!screens.empty()) {
        screens.top()->pause();
    }
    screens.push(screen);
}

void client::App::closeScreen() {
    if (screens.empty()) {
        return;
    }
    //qDebug() << "popping!";
    screens.pop();
    //qDebug() << "destroyed!";
    if (screens.empty()) {
        return;
    }
    //qDebug() << "calling resume!";
    screens.top()->resume();
}

client::App* client::App::getInstance() {
    return instance;
}

client::App* client::App::instance = nullptr;

void client::App::wheelEvent(QWheelEvent* event) {
    screens.top()->wheel(event);
}

void client::App::hover(QPoint point) {
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

void client::App::removeHovered(client::Widget* widget) {
    widget->setHovered(false);
    for (Widget* child : widget->children) {
        removeHovered(child);
    }
}

const QFont& client::App::getFont() const {
    return font;
}

const std::shared_ptr<QSettings>& client::App::getSettings() const {
    return settings;
}

QStack<std::shared_ptr<client::Screen>>& client::App::getScreens() {
    return screens;
}
