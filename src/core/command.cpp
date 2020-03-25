#include <QDebug>

#include "command.h"

core::Command::Command() {

}

core::Command::Command(QString name): name(name) {

}

const QString& core::Command::getName() const {
    return name;
}

void core::Command::setName(const QString& name) {
    Command::name = name;
}

void core::Command::setArguments(const QStringList& arguments) {
    Command::arguments = arguments;
}

core::Command core::Command::getCommand(QString text) {
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


