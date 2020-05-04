#include <QDebug>

#include "healthbar.h"

client::HealthBar::HealthBar(QPoint position, int width, int height, int currentHP, int maxHP):
        Widget(position), currentHP(currentHP), maxHP(maxHP) {
    setWidth(width);
    setHeight(height);
}

int client::HealthBar::getCurrentHp() const {
    return currentHP;
}

void client::HealthBar::setCurrentHp(int currentHp) {
    this->currentHP = currentHp;
}

int client::HealthBar::getMaxHp() const {
    return maxHP;
}

void client::HealthBar::setMaxHp(int maxHp) {
    this->maxHP = maxHp;
}

const QImage& client::HealthBar::getBackground() const {
    return background;
}

void client::HealthBar::setBackground(const QImage& background) {
    HealthBar::background = background;
}

const QImage& client::HealthBar::getHealthLine() const {
    return healthLine;
}

void client::HealthBar::setHealthLine(const QImage& healthLine) {
    HealthBar::healthLine = healthLine;
}

void client::HealthBar::paint(QPainter& painter) {
    painter.drawImage(QRect(0, 0, getWidth(), 70), background);
    int overlayWidth = getWidth();
    if (maxHP != 0) {
        overlayWidth = getWidth() * currentHP / maxHP;
    }
    QRect rect(0, 0, overlayWidth, 50);
    painter.drawImage(0, 0, healthLine.copy(rect));
}
