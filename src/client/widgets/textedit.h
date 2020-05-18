#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <functional>
#include <QImage>

#include "../widget.h"
#include "textview.h"

namespace client {

class TextEdit : public Widget {
  public:
    TextEdit(QPoint position = QPoint(0, 0), int height = 60,
                int width = 60);

    void paint(QPainter& painter) override;

    void keyPress(QKeyEvent* event) override;

  protected:
    void clicked(QPoint point, bool leftButton) override;

  public:

    const QImage& getBackgroundImage() const;

    void setBackgroundImage(const QImage& backgroundImage);

    const QImage& getSelectedImage() const;

    void setSelectedImage(const QImage& selectedImage);

    const std::shared_ptr<TextView>& getTextChildren() const;

    void setTextChildren(const std::shared_ptr<TextView>& text);

    const std::function<bool(QString)>& getValidate() const;

    void setValidate(const std::function<bool(QString)>& validate);

    int getSelectedWidth() const;

    void setSelectedWidth(int selectedWidth);

    int getSelectedHeight() const;

    void setSelectedHeight(int selectedHeight);

    bool isSelected() const;

    void setSelected(bool selected);

  private:
    QImage backgroundImage;

    QImage selectedImage;

    std::shared_ptr<TextView> textChildren;

    std::function<bool(QString text)> validate;

    int selectedWidth;

    int selectedHeight;

    bool selected;
};

}  // namespace client
#endif //TEXTEDIT_H
