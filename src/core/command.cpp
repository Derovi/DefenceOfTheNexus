#include <QDebug>

#include "command.h"

const QString& core::Command::getName() const {
    return name;
}

void core::Command::setName(const QString& name) {
    this->name = name;
}

void core::Command::setArguments(const QStringList& arguments) {
    this->arguments = arguments;
}

core::Command core::Command::fromCommandLine(QString text) {
    if (text.contains(' ')) {
        Command command = Command(text.left(text.indexOf(' ')));
        command.setArguments(text.right(text.length() - text.indexOf(' ') - 1).split(' '));
        return command;
    } else {
        return Command(text);
    }
}

const QStringList& core::Command::getArguments() const {
    return arguments;
}

core::Command::Command(const QString& name, const QStringList& arguments):
        name(name), arguments(arguments) {}



