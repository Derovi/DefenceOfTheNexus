#ifndef IMAGEBUTTON_H
#define IMAGEBUTTON_H

#include <functional>
#include <QImage>

#include "../widget.h"

namespace client {

class ImageButton : public Widget {
  public:
    ImageButton(QPoint position = QPoint(0, 0), int height = 60,
                int width = 60);

    virtual void paint(QPainter& painter);

    void setHeight(int height);

    void setWidth(int width);

    void setImage(QImage image);

    QImage getImage();

    bool clicked = false;

  private:
    QImage image;
};

}

#endif // IMAGEBUTTON_H
