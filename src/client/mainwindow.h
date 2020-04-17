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

    std::shared_ptr<QThread> getUiThread() const;

    static MainWindow* getInstance();

    static void runOnUiThread(std::function<void()> callback);

  private:
    void draw();

    QStack<std::shared_ptr<Screen>> screens;

    std::shared_ptr<QThread> uiThread;

    static MainWindow* instance;
};

}  // namespace client

#endif // MAINWINDOW_H
