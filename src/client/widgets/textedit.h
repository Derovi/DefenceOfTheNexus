#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QApplication>
#include <QRect>
#include "../widget.h"

namespace client {
class TextEdit : public Widget {
  public:
    TextEdit(const QPoint& position = QPoint(0, 0),
             const QString& text = "",
             const QFont& font = QApplication::font(),
             const QColor& color = Qt::black,
             int backgroundHeight = -1,
             int backgroundWidth = -1);

    void paint(QPainter& painter) override;

    void keyPress(QKeyEvent* event) override;

    const QString& getText() const;

    void setText(const QString& text);

    const QFont& getFont() const;

    void setFont(const QFont& font);

    const QColor& getColor() const;

    void setColor(const QColor& color);

    const QImage& getBackground() const;

    void setBackground(const QImage& background);

    void setTextSize(int textSize);

    int getTextSize() const;

    int getBackgroundHeight() const;

    void setBackgroundHeight(int backgroundHeight);

    int getBackgroundWidth() const;

    void setBackgroundWidth(int backgroundWidth);

    int getTextHeight() const;

    int getTextWidth() const;

    void setTextChecker(std::function<bool(QString)> textChecker);

    std::function<bool(QString)> getTextChecker() const;

  private:
    QString text;

    QFont font;

    QColor color;

    QImage background;

    int backgroundWidth;

    int backgroundHeight;

    std::function<bool(QString text)> textChecker;
};
}  // namespace client
#endif //TEXTEDIT_H
