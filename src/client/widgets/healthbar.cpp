#include <QDebug>

#include "healthbar.h"

client::HealthBar::HealthBar(QPoint position, int currentHP, int maxHP) : Widget(position) {
    setCurrentHp(currentHP);
    setMaxHp(maxHP);
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

int client::HealthBar::getWidth() const {
    return width;
}

void client::HealthBar::setWidth(int width) {
    HealthBar::width = width;
}

int client::HealthBar::getHeight() const {
    return height;
}

void client::HealthBar::setHeight(int height) {
    this->height = height;
}

void client::HealthBar::paint(QPainter& painter) {
    painter.drawImage(QRect(1296, 1593, 1250, 70), background);
    int overlayWidth = width;
    if (maxHP != 0) {
        overlayWidth = width * currentHP / maxHP;
    }
    QRect rect(0, 0, overlayWidth, 50);
    painter.drawImage(1306, 1603, healthLine.copy(rect));
}
