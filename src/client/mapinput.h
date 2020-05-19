#ifndef MAPINPUT_H
#define MAPINPUT_H

#include <QtCore/QString>
#include <QtCore/QPoint>

namespace client {

class GameMap;

class MapInput {
  public:
    explicit MapInput(GameMap* gameMap);

    bool isWaiting();

    void abort();

    void append(const QPoint& point);

    void setObjectType(const QString& objectType);

    const QString& getObjectType() const;

    const QVector<QPoint>& getPoints() const;

    GameMap* getGameMap() const;

  private:
    QString objectType;

    QVector<QPoint> points;

    GameMap* gameMap;
};

}

#endif  // MAPINPUT_H
