#include <QDebug>
#include <QtMath>

#include "../app.h"
#include "../screens/gamescreen.h"
#include "../windowmanager.h"

#include "gamemap.h"

client::GameMap::GameMap(QPoint position, int height, int width):
        Widget(position), cameraSpeed(60),
        showHitBoxes(false), showSprites(true), fixed(false) {
    setHeight(height);
    setWidth(width);
    setBoundsWidth(30);
    setDisplayBounds(QRect(0, 0, width, height));
}

bool client::GameMap::isFixed() const {
    return fixed;
}

void client::GameMap::setFixed(bool fixed) {
    GameMap::fixed = fixed;
}

const QRect& client::GameMap::getDisplayBounds() const {
    return displayBounds;
}

void client::GameMap::setDisplayBounds(const QRect& displayBounds) {
    GameMap::displayBounds = displayBounds;
}

void client::GameMap::paint(QPainter& painter) {
    qDebug() << "client" << gameWorld->getObjects()[0]->getPosition();
    auto gameScreen = dynamic_cast<GameScreen*>(getParent());
    if (fixed) {
        if (gameWorld->getObjects().contains(0)) {
            int objectId = gameScreen->getInterface()->getSelectedUnitId();
            centerWindow(QPoint(gameWorld->getObjects()[objectId]->getPosition().x() + 1,
                                gameWorld->getObjects()[objectId]->getPosition().y() + 1));
        }
    } else {
        QPoint cursor = QPoint(window_manager::get_x4k(
                App::getInstance()->mapFromGlobal(App::getInstance()->cursor().pos()).x()),
                               window_manager::get_y4k(
                                       App::getInstance()->mapFromGlobal(
                                               App::getInstance()->cursor().pos()).y()));
        if (isPointOnBounds(cursor)) {
            QVector2D vector(cursor.x() - 1920, cursor.y() - 1080);
            vector.normalize();
            centerWindow(getWindowCenter() + vector.toPoint() * cameraSpeed);
        }
    }

    if (timerMainMusic == 0) {
        mainPlayer.setMedia(QUrl::fromLocalFile("sounds/main_song.wav"));
        mainPlayer.setVolume(50);
        mainPlayer.play();
        timerMainMusic = 50 * 120;
    } else {
        --timerMainMusic;
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
            hitBoxPainter.drawText(QPoint(20, 0),
                                   QString::number(object->getId()));
            hitBoxPainter.rotate(object->getRotationAngle());
            hitBoxPainter.setPen(QPen(QBrush(Qt::green),
                                      8, Qt::SolidLine,
                                      Qt::SquareCap, Qt::MiterJoin));
            hitBoxPainter.drawPolygon(object->getHitbox());
            hitBoxPainter.setPen(QPen(QBrush(QColor(0, 0, 0)),
                                      8, Qt::SolidLine,
                                      Qt::SquareCap, Qt::MiterJoin));
        }
    }

    while (!gameScreen->getMultiplayerInterface()->getEventQueue().empty()) {
        handleEvent(gameScreen->getMultiplayerInterface()->getEventQueue().takeFirst());
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

void client::GameMap::clicked(QPoint point, bool leftButton) {
    point = getTransformToMap().map(point);
    auto gameScreen = dynamic_cast<GameScreen*>(getParent());
    if (leftButton) {
        auto object = gameWorld->objectAt(point);
        if (object) {
            gameScreen->getInterface()->setSelectedUnitId(object->getId());
        }
        return;
    }
    int objectId = gameScreen->getInterface()->getSelectedUnitId();
    if (!gameWorld->getObjects().contains(objectId)) {
        qDebug() << "No such object!";
        return;
    }
    auto target = gameWorld->objectAt(point);
    if (gameWorld->getObjects()[objectId]->getTeam() != gameScreen->getTeam()) {
        qDebug() << "No permission!";
        return;
    }
    if (target != nullptr && target->hasAttribute("resource")) {
        gameScreen->getMultiplayerInterface()->sendCommand(core::Command("mine_resource", {
                QString::number(objectId), QString::number(target->getId())}));
    } else if (target != nullptr && target->hasAttribute("damageable")) {
        gameScreen->getMultiplayerInterface()->sendCommand(core::Command(core::Command("attack",
                                                                                       {QString::number(
                                                                                               objectId),
                                                                                        QString::number(
                                                                                                target->getId())})));
    } else {
        gameScreen->getMultiplayerInterface()->sendCommand(core::Command(
                core::Command("change_move_target",
                              {QString::number(objectId), QString::number(point.x()),
                               QString::number(point.y())})));
    }
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
    int64_t deltaTime = getDeltaTime();
    background.update(deltaTime);
    for (int x = (displayBounds.x() / background.getFrameWidth() - 1) * background.getFrameWidth();
         x < displayBounds.x() + displayBounds.width();
         x += background.getFrameWidth()) {
        for (int y =
                (displayBounds.y() / background.getFrameHeight() - 1) * background.getFrameHeight();
             y < displayBounds.y() + displayBounds.height();
             y += background.getFrameHeight()) {
            background.draw(painter,
                            QRect(x, y, background.getFrameWidth(), background.getFrameHeight()));
        }
    }
}

const QHash<int64_t, std::shared_ptr<client::GraphicsObject>>&
client::GameMap::getGraphicsObjects() const {
    return graphicsObjects;
}

void client::GameMap::buildCommand(const QString& objectType) {

}

void client::GameMap::handleEvent(const core::Event& event) {
    //!TODO handle event
    if (event.getType() == core::Event::Type::HIT_EVENT) {
        qDebug() << "handled hit event! Damager id: " << event.getArguments();
        int id = event.getArguments()[0].toLongLong();
        playSound(QStringList({QString("sounds/sword_attack.wav"),
                               QString::number(gameWorld->getObjects()[id]->getPosition().x()),
                               QString::number(gameWorld->getObjects()[id]->getPosition().y())}));
    }
    if (event.getType() == core::Event::Type::MINE_EVENT) {
        int id = event.getArguments()[0].toLongLong();
        playSound(QStringList({QString("sounds/mine.wav"),
                               QString::number(gameWorld->getObjects()[id]->getPosition().x()),
                               QString::number(gameWorld->getObjects()[id]->getPosition().y())}));
    }

}

void client::GameMap::playSound(QStringList arguments) {
    double distance = qSqrt((getWindowCenter().x() - (arguments[1].toInt())) *
                            (getWindowCenter().x() - (arguments[1].toInt())) +
                            (getWindowCenter().y() - (arguments[2].toInt())) *
                            (getWindowCenter().y() - (arguments[2].toInt())));
    int volume = 50 - distance / 100;
    volume = std::max(volume, 0);
    bool ok = false;
    for (auto& player: musicPlayers) {
        if (player->isAvailable()) {
            ok = true;
            player->setMedia(QUrl::fromLocalFile(arguments[0]));
            player->setVolume(volume);
            player->play();
            break;
        }
    }
    if (!ok) {
        auto* player = new QMediaPlayer;
        musicPlayers.push_back(std::make_shared<QMediaPlayer>(player));
        musicPlayers.back()->setMedia(QUrl::fromLocalFile(arguments[0]));
        musicPlayers.back()->setVolume(volume);
        musicPlayers.back()->play();
    }
}

