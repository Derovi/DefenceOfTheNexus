#include "windowmanager.h"
#include "properties.h"

int client::window_manager::get_real_x(int x4k) {
    return x4k * properties::width / width4k;
}

int client::window_manager::get_real_y(int y4k) {
    return y4k * properties::height / height4k;
}

int client::window_manager::get_x4k(int x) {
    return x * width4k / properties::width;
}

int client::window_manager::get_y4k(int y) {
    return y * height4k / properties::height;
}
