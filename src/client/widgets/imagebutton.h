#ifndef IMAGEBUTTON_H
#define IMAGEBUTTON_H

#include <functional>
#include <QImage>

#include "../widget.h"
#include "textview.h"

namespace client {

class ImageButton : public Widget {
  public:
    ImageButton(QPoint position = QPoint(0, 0), int height = 60,
                int width = 60);

    void paint(QPainter& painter) override;

    void setHeight(int height);

    void setWidth(int width);

    void setImage(QImage image);

    QImage getImage();

  private:
    QImage image;

    QImage hoverImage;

    TextView* textChildren;
};

}

#endif // IMAGEBUTTON_H
