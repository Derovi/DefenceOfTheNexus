#include "windowmanager.h"

WindowManager::WindowManager(int width, int height) :
        window_height(height), window_width(width) {}

void WindowManager::update(int width, int height) {
    this->window_width = width;
    this->window_height = height;
}

int WindowManager::get_real_x(int x4k) {
    return x4k * window_width / width4k;
}

int WindowManager::get_real_y(int y4k) {
    return y4k * window_height / height4k;
}

int WindowManager::get_x4k(int x) {
    return x * width4k / window_width;
}

int WindowManager::get_y4k(int y) {
    return y * height4k / window_height;
}
