#include "command.h"

#include <utility>

const QString& core::Command::getName() const {
    return name;
}

void core::Command::setName(const QString& name) {
    this->name = name;
}

void core::Command::setArguments(const QStringList& arguments) {
    this->arguments = arguments;
}

core::Command core::Command::fromCommandLine(const QString& text) {
    if (text.contains(' ')) {
        QStringList words = text.split(' ');
        QString command = words.takeFirst();
        return Command(command, words);
    } else {
        return Command(text);
    }
}

const QStringList& core::Command::getArguments() const {
    return arguments;
}

core::Command::Command(const QString& name, const QStringList& arguments):
        name(name), arguments(arguments) {}



