#include "strategy.h"

core::Object* server::Strategy::getObject() const {
    return object;
}

bool server::Strategy::isPaused() const {
    return paused;
}

server::Strategy::Strategy(core::Object* object) : object(object) {}

void server::Strategy::pause() {
    if (paused) {
        return;
    }
    paused = true;
}

void server::Strategy::resume() {
    if (!paused) {
        return;
    }
    paused = false;
}

server::Strategy::~Strategy() = default;
