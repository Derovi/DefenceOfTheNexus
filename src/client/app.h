#ifndef APP_H
#define APP_H

#include <QWidget>
#include <QThread>
#include <QStack>

#include "widget.h"
#include "screen.h"

namespace client {

class WindowManager;

class App : public QWidget {

  public:
    App();

    void paintEvent(QPaintEvent*);

    void mousePressEvent(QMouseEvent*);

    void openScreen(const std::shared_ptr<Screen>& screen);

    void closeScreen();

  protected:
    void wheelEvent(QWheelEvent* event) override;

  public:
    QThread* getUiThread() const;

    static App* getInstance();

    static void runOnUiThread(std::function<void()> callback);

    const QFont& getFont() const;

  private:
    void draw();

    void removeHovered(Widget* widget);

    void hover(QPoint point);

    QStack<std::shared_ptr<Screen>> screens;

    QFont font;

    QThread* uiThread;

    static App* instance;
};

}  // namespace client

#endif //APP_H
