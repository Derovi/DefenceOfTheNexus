#ifndef MOVING_H
#define MOVING_H

#include <memory>
#include <QVector2D>

#include "attribute.h"

namespace core {

class Moving : public Attribute {
  public:
    Moving();

    Moving(QVector2D direction, double speed, double maxSpeed);

    virtual ~Moving() = default;

    const QVector2D& getDirection() const;

    double getSpeed() const;

    double getMaxSpeed() const;

    void setMaxSpeed(double maxSpeed);

    virtual void setDirection(const QVector2D& direction);

    virtual void setSpeed(double speed);

    virtual void set(const Moving& properties);

    static QString attributeName;

    QString getAttributeName() override;

    std::shared_ptr<Attribute> clone() override;

  private:
    QVector2D direction;
    double speed;
    double maxSpeed;
};

}  // namespace core

#endif // MOVING_H
