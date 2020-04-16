#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QThread>

#include "widget.h"

namespace client {

class WindowManager;

class MainWindow : public QWidget {

  public:
    MainWindow();

    void paintEvent(QPaintEvent*);

    void mousePressEvent(QMouseEvent*);

    std::shared_ptr<QThread> getUiThread() const;

  private:
    void draw();

    QVector<std::shared_ptr<Widget>> widgets;

    std::shared_ptr<QThread> uiThread;
};

}  // namespace client

#endif // MAINWINDOW_H
