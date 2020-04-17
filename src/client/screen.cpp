#include "screen.h"

void client::Screen::pause() {
    if (state == PAUSED) {
        return;
    }
    state = PAUSED;
    onPaused();
}

void client::Screen::resume() {
    if (state == CURRENT) {
        return;
    }
    state = CURRENT;
    onResumed();
}

client::ScreenState client::Screen::getState() const {
    return state;
}
