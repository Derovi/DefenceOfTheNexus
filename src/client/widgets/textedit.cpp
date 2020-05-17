#include <QDebug>

#include <QtCore/QString>
#include "textedit.h"

client::TextEdit::TextEdit(const QPoint& position, const QString& text, const QFont& font,
                           const QColor& color, int backgroundHeight,
                           int backgroundWidth, bool selected):
        Widget(position), text(text), font(font), color(color), selected(selected) {
    setHeight(backgroundHeight);
    setWidth(backgroundWidth);
}

void client::TextEdit::paint(QPainter& painter) {
    if (!hover.isNull() && selected) {
        painter.drawImage(boundsRect(), hover);

    } else if (!background.isNull()) {
        painter.drawImage(boundsRect(), background);
    }

    painter.setFont(font);
    QPen pen = painter.pen();
    pen.setColor(color);
    painter.setPen(pen);

    if (backgroundWidth > 0 && backgroundHeight > 0) {
        painter.drawText(boundsRect(),Qt::AlignCenter, text);
    } else {
        painter.drawText(QPoint(0, 0), text);
    }
}


const QString& client::TextEdit::getText() const {
    return text;
}

void client::TextEdit::setText(const QString& text) {
    TextEdit::text = text;
}

const QFont& client::TextEdit::getFont() const {
    return font;
}

void client::TextEdit::setFont(const QFont& font) {
    TextEdit::font = font;
}

const QColor& client::TextEdit::getColor() const {
    return color;
}

void client::TextEdit::setColor(const QColor& color) {
    TextEdit::color = color;
}

const QImage& client::TextEdit::getBackground() const {
    return background;
}

void client::TextEdit::setBackground(const QImage& background) {
    TextEdit::background = background;
}

int client::TextEdit::getTextSize() const {
    return font.pixelSize();
}

void client::TextEdit::setTextSize(int textSize) {
    font.setPixelSize(textSize);
}

int client::TextEdit::getBackgroundHeight() const {
    return backgroundHeight;
}

void client::TextEdit::setBackgroundHeight(int backgroundHeight) {
    TextEdit::backgroundHeight = backgroundHeight;
}

int client::TextEdit::getBackgroundWidth() const {
    return backgroundWidth;
}

void client::TextEdit::setBackgroundWidth(int backgroundWidth) {
    TextEdit::backgroundWidth = backgroundWidth;
}

int client::TextEdit::getTextHeight() const {
    return QFontMetrics(font).capHeight();
}

int client::TextEdit::getTextWidth() const {
    return QFontMetrics(font).width(text);
}

void client::TextEdit::keyPress(QKeyEvent* event) {
    if (selected) {
        if (event->key() == Qt::Key_Backspace) {
            text.chop(1);
        } else if (textChecker(text + event->text())) {
            text.append(event->text());
        }
    }

}

void client::TextEdit::clicked(QPoint point, bool leftButton) {
    selected = true;
}

void client::TextEdit::setTextChecker(std::function<bool(QString)> textChecker) {
    TextEdit::textChecker = textChecker;
}

std::function<bool(QString)> client::TextEdit::getTextChecker() const {
    return textChecker;
}

bool client::TextEdit::isSelected() const {
    return selected;
}

void client::TextEdit::setSelected(bool selected) {
    TextEdit::selected = selected;
}

const QImage& client::TextEdit::getHover() const {
    return hover;
}

void client::TextEdit::setHover(const QImage& hover) {
    TextEdit::hover = hover;
}
