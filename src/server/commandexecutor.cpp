#include <QDebug>

#include "../core/gameworld.h"

#include "commandexecutor.h"

server::CommandExecutor::CommandExecutor() {}

server::CommandExecutor::CommandExecutor(core::GameWorld* gameWorld): gameWorld(gameWorld) {
    registerCommands();
}


bool server::CommandExecutor::executeCommand(const core::Command& command) {
    if (!commands.contains(command.getName().normalized(QString::NormalizationForm_D))) {
        return false;
    }
    return commands[command.getName().normalized(QString::NormalizationForm_D)](
            command.getArguments());
}

void server::CommandExecutor::unregisterCommand(QString name) {
    if (commands.contains(name.normalized(QString::NormalizationForm_D))) {
        commands.erase(commands.find(name.normalized(QString::NormalizationForm_D)));
    }
}

void server::CommandExecutor::registerCommand(QString name,
                                              std::function<bool(QStringList)> executable) {
    commands.insert(name.normalized(QString::NormalizationForm_D), executable);
}

bool server::CommandExecutor::testCommand(QStringList arguments) {
    for (QString argument : arguments) {
        qDebug() << argument;
    }
    return true;
}

void server::CommandExecutor::registerCommands() {
    registerCommand("test", testCommand);
}

