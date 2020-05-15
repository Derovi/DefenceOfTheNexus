#ifndef MOVING_H
#define MOVING_H

#include <memory>

#include <QVector2D>

#include "../attribute.h"

namespace core {

class Moving : public Attribute {
  public:
    inline static const QString attributeName = "moving";

    Moving();

    Moving(QVector2D direction, double speed, double maxSpeed);

    ~Moving() override = default;

    const QVector2D& getDirection() const;

    double getSpeed() const;

    double getMaxSpeed() const;

    void setMaxSpeed(double maxSpeed);

    void setDirection(const QVector2D& direction);

    void setSpeed(double speed);

    void set(const Moving& properties);

    QString getAttributeName() override;

    std::shared_ptr<Attribute> clone() override;

    bool operator==(core::Moving moving);

  private:
    QVector2D direction;
    double speed;
    double maxSpeed;
};

}  // namespace core

#endif  // MOVING_H
