#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

namespace client {

class WindowManager {
  public:
    WindowManager(int width, int height);

    // coverts from 4k to current display size
    int get_real_x(int x4k);

    int get_real_y(int y4k);

    int get_x4k(int x);

    int get_y4k(int y);

    void update(int width, int height);

  private:
    int window_height;
    int window_width;

    const int width4k = 3840;
    const int height4k = 2160;

    friend class MainWindow;
};

}  // namespace client

#endif // WINDOWMANAGER_H
