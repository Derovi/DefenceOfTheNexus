#ifndef TEXTVIEW_H
#define TEXTVIEW_H

#include <QApplication>
#include <QRect>

#include "../widget.h"

namespace client {

class TextView : public Widget {
  public:
    TextView(const QPoint& position = QPoint(0, 0), const QString& text = "TextView",
             const QFont& font = QApplication::font(),
             const QColor& color = Qt::black,
             int height = -1,
             int width = -1);

    const QString& getText() const;

    void setText(const QString& text);

    const QFont& getFont() const;

    void setFont(const QFont& font);

    const QColor& getColor() const;

    void setColor(const QColor& color);

    void setTextSize(int textSize);

    int getTextSize() const;

    int getTextHeight() const;

    int getTextWidth() const;

  private:
    void paint(QPainter& painter) override;

  private:
    QString text;

    QFont font;

    QColor color;
};

}

#endif //TEXTVIEW_H
