#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include "../widget.h"
#include "../sprite.h"

namespace client {
class HealthBar : public Widget {
  public:
    HealthBar(QPoint position = QPoint(0, 0), int currentHP = 100,
              int maxHP = 100);

    int getCurrentHp() const;

    void setCurrentHp(int currentHp);

    int getMaxHp() const;

    void setMaxHp(int maxHp);

    const QImage& getBackground() const;

    void setBackground(const QImage& background);

    const QImage& getHealthLine() const;

    void setHealthLine(const QImage& healthLine);

    int getWidth() const;

    void setWidth(int width);

    int getHeight() const;

    void setHeight(int height);

    void paint(QPainter& painter) override;

  private:
    int currentHP;
    int maxHP;

    int width;
    int height;

    QImage background;
    QImage healthLine;

};
} // namespace client
#endif //HEALTHBAR_H
