#ifndef MINING_H
#define MINING_H

#include <memory>

#include <QString>

#include "../attribute.h"

namespace core {

class Mining : public Attribute {
  public:
    inline static const QString attributeName = "mining";

    Mining();

    Mining(int miningSpeed, int miningDelay, double miningRadius);

    int getMiningSpeed() const;

    int getMiningDelay() const;

    int getCurrentDelay() const;

    double getMiningRadius() const;

    bool isMining() const;

    void setMiningSpeed(int speed);

    void setMiningDelay(int delay);

    void setCurrentDelay(int delay);

    void setMiningRadius(double radius);

    void setMining(bool mining);

    QString getAttributeName() override;

    std::shared_ptr<Attribute> clone() override;

    bool operator==(core::Mining);

  private:
    bool mining;
    int miningSpeed;
    int miningDelay;
    int currentDelay;
    double miningRadius;
};

}  // namespace core

#endif  // MINING_H
