//
// Created by derovi on 4/10/2020.
//

#include "strategy.h"

core::Object* server::Strategy::getObject() const {
    return object;
}

server::Strategy::Strategy(core::Object* object) : object(object) {}

bool server::Strategy::isPaused() const {
    return paused;
}

void server::Strategy::setPaused(bool paused) {
    Strategy::paused = paused;
}
