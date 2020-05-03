#include <QDebug>

#include "../app.h"

#include "gamemap.h"

client::GameMap::GameMap(QPoint position, int height, int width):
        Widget(position), commandQueue(nullptr),
        showHitBoxes(false), showSprites(true) {
    setHeight(height);
    setWidth(width);
    setDisplayBounds(QRect(0, 0, width, height));
}

const QRect& client::GameMap::getDisplayBounds() const {
    return displayBounds;
}

void client::GameMap::setDisplayBounds(const QRect& displayBounds) {
    GameMap::displayBounds = displayBounds;
}

void client::GameMap::paint(QPainter& painter) {
    if (gameWorld->getObjects().contains(0)) {
        centerWindow(QPoint(gameWorld->getObjects()[0]->getPosition().x() + 1,
                           gameWorld->getObjects()[0]->getPosition().y() + 1));
    }

    // paint transform
    painter.setTransform(getTransformToWidget(), true);

    // draw background
    if (!background.getSource().isNull()) {
        drawBackground(painter);
    }

    // renew graphics object list
    for (std::shared_ptr<core::Object> object : gameWorld->getObjects()) {
        if (!graphicsObjects.contains(object->getId())) {
            graphicsObjects.insert(object->getId(),
                                   std::make_shared<GraphicsObject>(object));
        }
    }

    QVector<int> eraseList;

    for (auto iterator = graphicsObjects.begin();
         iterator != graphicsObjects.end();
         ++iterator) {
        if (!gameWorld->getObjects().contains(iterator.key())) {
            eraseList.push_back(iterator.key());
        }
    }

    for (int id : eraseList) {
        graphicsObjects.remove(id);
    }

    // update graphics objects
    int64_t deltaTime = getDeltaTime();

    if (showSprites) {
        for (std::shared_ptr<GraphicsObject> graphicsObject : graphicsObjects.values()) {
            graphicsObject->update(painter.transform(), deltaTime);
    }
}

    if (showHitBoxes) {
        for (const std::shared_ptr<core::Object>& object : gameWorld->getObjects().values()) {
            QPainter hitBoxPainter(App::getInstance());
            hitBoxPainter.setTransform(painter.transform());
            QFont font = hitBoxPainter.font();
            font.setPointSize(40);
            font.setBold(true);
            hitBoxPainter.setFont(font);
            hitBoxPainter.translate(object->getPosition().x(), object->getPosition().y());
            hitBoxPainter.rotate(object->getRotationAngle());
            hitBoxPainter.setPen(QPen(QBrush(Qt::green),
                                      8, Qt::SolidLine,
                                      Qt::SquareCap, Qt::MiterJoin));
            hitBoxPainter.drawPolygon(object->getHitbox());
            hitBoxPainter.setPen(QPen(QBrush(QColor(0, 0, 0)),
                                      8, Qt::SolidLine,
                                      Qt::SquareCap, Qt::MiterJoin));
            hitBoxPainter.drawText(object->getPosition() - QPoint(20, 0),
                                   QString::number(object->getId()));
        }
    }
}

const std::shared_ptr<core::GameWorld>& client::GameMap::getGameWorld() const {
    return gameWorld;
}

void client::GameMap::setGameWorld(const std::shared_ptr<core::GameWorld>& gameWorld) {
    GameMap::gameWorld = gameWorld;
}

QTransform client::GameMap::getTransformToWidget() const {
    return QTransform(1, 0, 0, 1, -displayBounds.x(), -displayBounds.y()) *
           QTransform(static_cast<double>(width) / displayBounds.width(), 0, 0,
                      static_cast<double>(height) / displayBounds.height(), 0, 0);
}

QTransform client::GameMap::getTransformToMap() const {
    return getTransformToWidget().inverted();
}

void client::GameMap::clicked(QPoint point) {
    point = getTransformToMap().map(point);
    auto object = gameWorld->objectAt(point);
    if (object != nullptr && object->hasAttribute("resource")) {
        commandQueue->push(core::Command("mine_resource", {
           "0", QString::number(object->getId())}));
    } else {
        commandQueue->push(core::Command("change_move_target", {"0", QString::number(point.x()),
                                                                QString::number(point.y())}));
    }
}

const std::shared_ptr<Queue<core::Command>>& client::GameMap::getCommandQueue() const {
    return commandQueue;
}

void client::GameMap::setCommandQueue(const std::shared_ptr<Queue<core::Command>>& commandQueue) {
    GameMap::commandQueue = commandQueue;
}

int client::GameMap::getWindowHeight() const {
    return displayBounds.height();
}

int client::GameMap::getWindowWidth() const {
    return displayBounds.width();
}

QPoint client::GameMap::getWindowSize() const {
    return QPoint(getWindowWidth(), getWindowHeight());
}

QPoint client::GameMap::getWindowCenter() const {
    return displayBounds.center();
}

void client::GameMap::centerWindow(const QPoint& point) {
    setDisplayBounds(QRect(point.x() - getWindowWidth() / 2.0,
                           point.y() - getWindowHeight() / 2.0,
                           getWindowWidth(), getWindowHeight()));
}

void client::GameMap::changeWindowWidth(int width) {
    QPoint center = getWindowCenter();
    displayBounds.setWidth(width);
    centerWindow(center);
}

void client::GameMap::changeWindowHeight(int height) {
    QPoint center = getWindowCenter();
    displayBounds.setHeight(height);
    centerWindow(center);
}

void client::GameMap::resizeWindow(const QPoint& size) {
    changeWindowWidth(size.x());
    changeWindowHeight(size.y());
}

void client::GameMap::scaleWindow(double scaling) {
    changeWindowWidth(getWindowWidth() * scaling);
    changeWindowHeight(getWindowHeight() * scaling);
}

void client::GameMap::wheelEvent(QWheelEvent* event) {
    scaleWindow(event->angleDelta().y() > 0 ? 1 / 1.03 : 1.03);
}

bool client::GameMap::isShowHitBoxes() const {
    return showHitBoxes;
}

void client::GameMap::setShowHitBoxes(bool showHitBoxesMode) {
    GameMap::showHitBoxes = showHitBoxesMode;
}

bool client::GameMap::isShowSprites() const {
    return showSprites;
}

void client::GameMap::setShowSprites(bool showSprites) {
    GameMap::showSprites = showSprites;
}

const client::Sprite& client::GameMap::getBackground() const {
    return background;
}

void client::GameMap::setBackground(const client::Sprite& background) {
    this->background = background;
}

void client::GameMap::setBackground(const QPixmap& background) {
    this->background = Sprite(background);
}

void client::GameMap::drawBackground(QPainter& painter) {
    int64_t deltaTime = lastPaintTime.msecsTo(QDateTime::currentDateTime());
    background.update(deltaTime);
    for (int x = (displayBounds.x() / background.getFrameWidth() - 1) * background.getFrameWidth();
         x < displayBounds.x() + displayBounds.width();
         x += background.getFrameWidth()) {
        for (int y = (displayBounds.y() / background.getFrameHeight() - 1) * background.getFrameHeight();
             y < displayBounds.y() + displayBounds.height();
             y += background.getFrameHeight()) {
            background.draw(painter,
                           QRect(x, y, background.getFrameWidth(), background.getFrameHeight()));
        }
    }
}
