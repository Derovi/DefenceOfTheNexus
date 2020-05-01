#ifndef CHOOSER_H
#define CHOOSER_H

#include <QApplication>
#include <QRect>

#include "../widget.h"
#include "imagebutton.h"

namespace client {

class Chooser : public Widget {
  public:
    Chooser(QPoint position, int height, int width);

    void paint(QPainter& painter) override;

    int getSelected() const;

    const std::function<void(int)>& getOnChanged() const;

    void setOnChanged(const std::function<void(int)>& onChanged);

    void setBackground(const QImage& background);

    const QImage& getBackground() const;

    const QStringList& getOptions() const;

    void setOptions(const QStringList& options);

    int getTextWidth() const;

    void setTextWidth(int textWidth);

    int getButtonWidth() const;

    void setButtonWidth(int buttonWidth);

    ImageButton* getLeftButton() const;

    ImageButton* getRightButton() const;

    TextView* getTextView() const;

    void setSelected(int selected);

  private:
    void leftClick();

    void rightClick();

    void update();

    QStringList options;

    QImage background;

    std::function<void(int selected)> onChanged;

    ImageButton* leftButton;

    ImageButton* rightButton;

    TextView* textView;

    int buttonWidth;

    int textWidth;

    int selected;
};

}

#endif  // CHOOSER_H
