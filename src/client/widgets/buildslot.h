#ifndef BUILDSLOT_H
#define BUILDSLOT_H

#include <functional>
#include <QImage>

#include "../widget.h"

namespace client {

class BuildSlot : public Widget {
  public:
    BuildSlot(QPoint position = QPoint(0, 0), int height = 60,
                int width = 60);

    void paint(QPainter& painter) override;

    int getHoverWidth() const;

    void setHoverWidth(int hoverWidth);

    int getHoverHeight() const;

    void setImage(QImage image);

    QImage getImage();

    const QImage& getHoverImage() const;

    void setHoverImage(const QImage& hoverImage);

    void setHoverHeight(int hoverHeight);

  private:
    QImage image;

    QImage hoverImage;

    int hoverWidth;

    int hoverHeight;
};

}

#endif  // BUILDSLOT_H
