#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include "../widget.h"
#include "../sprite.h"
#include "textview.h"

namespace client {

class HealthBar : public Widget {
  public:
    HealthBar(QPoint position = QPoint(0, 0), int width = 1250, int height = 70,
              int currentHP = 0,
              int maxHP = 0);

    int getCurrentHp() const;

    void setCurrentHp(int currentHp);

    int getMaxHp() const;

    void setMaxHp(int maxHp);

    const QImage& getBackground() const;

    void setBackground(const QImage& background);

    const QImage& getHealthLine() const;

    void setHealthLine(const QImage& healthLine);

    void paint(QPainter& painter) override;

  private:
    QImage background;
    QImage healthLine;

    TextView* hpView;

    int currentHP;
    int maxHP;
};

} // namespace client

#endif //HEALTHBAR_H
