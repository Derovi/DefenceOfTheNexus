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

    const std::shared_ptr<ImageButton>& getLeftButton() const;

    const std::shared_ptr<ImageButton>& getRightButton() const;

    const std::shared_ptr<TextView>& getTextView() const;

  private:
    void leftClick();

    void rightClick();

    QStringList options;

    QImage background;

    std::function<void(int selected)> onChanged;

    std::shared_ptr<ImageButton> leftButton;

    std::shared_ptr<ImageButton> rightButton;

    std::shared_ptr<TextView> textView;

    int textWidth;

    int selected;
};

}

#endif  // CHOOSER_H
