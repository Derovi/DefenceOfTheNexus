#include "event.h"

#include <utility>

core::Event::Event(core::Event::Type type, QStringList arguments):
        type(type), arguments(std::move(arguments)) {}

core::Event::Type core::Event::getType() const {
    return type;
}

void core::Event::setType(core::Event::Type type) {
    Event::type = type;
}

const QStringList& core::Event::getArguments() const {
    return arguments;
}

void core::Event::setArguments(const QStringList& arguments) {
    Event::arguments = arguments;
}
