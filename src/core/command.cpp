//
// Created by derovi on 3/24/2020.
//

#include "command.h"

core::Command::Command() {

}

core::Command::Command(QString name) : name(name) {

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
    Command command = Command(text);
    if (text.contains(' ')) {
        command.setArguments(text.right(text.indexOf(' ')).split(' '));
    }
    return command;
}

const QStringList& core::Command::getArguments() const {
    return arguments;
}


