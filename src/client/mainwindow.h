#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QThread>
#include <QStack>

#include "widget.h"
#include "screen.h"

namespace client {

class WindowManager;

class MainWindow : public QWidget {

  public:
    MainWindow();

    void paintEvent(QPaintEvent*);

    void mousePressEvent(QMouseEvent*);

    void openScreen(const std::shared_ptr<Screen>& screen);

    void closeScreen();

  protected:
    void wheelEvent(QWheelEvent* event) override;

  public:
    QThread* getUiThread() const;

    static MainWindow* getInstance();

    static void runOnUiThread(std::function<void()> callback);

  private:
    void draw();

    QStack<std::shared_ptr<Screen>> screens;

    QThread* uiThread;

    static MainWindow* instance;
};

}  // namespace client

#endif // MAINWINDOW_H
