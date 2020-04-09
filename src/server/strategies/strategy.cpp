#include "strategy.h"

core::Object* server::Strategy::getObject() const {
    return object;
}

bool server::Strategy::isPaused() const {
    return paused;
}

void server::Strategy::setPaused(bool paused) {
    Strategy::paused = paused;
}
