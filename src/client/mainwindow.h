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

  private:
    void draw();

    QVector<std::shared_ptr<Widget>> widgets;

    std::shared_ptr<QThread> uiThread;

    QStack<std::shared_ptr<Screen>> screens;
};

}  // namespace client

#endif // MAINWINDOW_H
