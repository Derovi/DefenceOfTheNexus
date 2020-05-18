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

    int getHoverWidth() const;

    void setHoverWidth(int hoverWidth);

    int getHoverSize() const;

    void setHoverSize(int hoverSize);

    void setImage(QImage image);

    QImage getImage();

    const QImage& getHoverImage() const;

    void setHoverImage(const QImage& hoverImage);

    const std::shared_ptr<TextView>& getTextChildren() const;

    void setTextChildren(const std::shared_ptr<TextView>& textChildren);

    int getHoverHeight() const;

    void setHoverHeight(int hoverHeight);

  protected:
    QImage image;

    QImage hoverImage;

    std::shared_ptr<TextView> textChildren;

    int hoverWidth;

    int hoverHeight;
};

}

#endif // IMAGEBUTTON_H


