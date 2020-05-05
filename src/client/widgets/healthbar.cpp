#include <QDebug>

#include "../app.h"

#include "healthbar.h"

client::HealthBar::HealthBar(QPoint position, int width, int height, int currentHP, int maxHP):
        Widget(position), currentHP(currentHP), maxHP(maxHP) {
    setWidth(width);
    setHeight(height);

    QFont font = App::getInstance()->getFont();
    font.setPixelSize(57);
    hpView = new TextView(QPoint(0, 0), "", font);
    addChild(hpView);
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
    hpView->setText("");
    if (maxHP != 0) {
        overlayWidth = getWidth() * currentHP / maxHP;
        hpView->setText(QString::number(currentHP) + " / " + QString::number(maxHP));
        hpView->setPosition(QPoint(
                getWidth() / 2.0 - hpView->getTextWidth() / 2.0,
                getHeght() / 2.0 + hpView->getTextHeight() / 2.0 - 12
        ));
    }
    QRect rect(0, 0, overlayWidth, 50);
    painter.drawImage(0, 0, healthLine.copy(rect));
}
