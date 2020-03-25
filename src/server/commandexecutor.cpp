//
// Created by derovi on 3/24/2020.
//

#include <QDebug>
#include "commandexecutor.h"
#include "../core/gameworld.h"

server::CommandExecutor::CommandExecutor() {

}

server::CommandExecutor::CommandExecutor(core::GameWorld* gameWorld) : gameWorld(gameWorld) {
    registerCommand("test", testCommand);
}



bool server::CommandExecutor::executeCommand(const core::Command& command) {
    if (!commands.contains(command.getName())) {
        return false;
    }
    return commands[command.getName()](command.getArguments());
}

void server::CommandExecutor::unregisterCommand(QString name) {
    if (commands.contains(name)) {
        commands.erase(commands.find(name));
    }
}

void server::CommandExecutor::registerCommand(QString name,
                                              std::function<bool(QStringList)> executable) {
    commands.insert(name, executable);
}

bool server::CommandExecutor::testCommand(QStringList arguments) {
    for (QString argument : arguments) {
        qDebug() << argument;
    }
    return false;
}

