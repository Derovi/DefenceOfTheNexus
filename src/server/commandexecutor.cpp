#include <QDebug>

#include "../core/gameworld.h"
#include "../core/moving.h"

#include "commandexecutor.h"

server::CommandExecutor::CommandExecutor() {}

server::CommandExecutor::CommandExecutor(core::GameWorld* gameWorld): gameWorld(gameWorld) {
    registerCommands();
}


bool server::CommandExecutor::executeCommand(const core::Command& command) {
    if (!commands.contains(command.getName().normalized(QString::NormalizationForm_D))) {
        return false;
    }
    return (this->*commands[command.getName().normalized(QString::NormalizationForm_D)])(
            command.getArguments());
}

void server::CommandExecutor::unregisterCommand(QString name) {
    if (commands.contains(name.normalized(QString::NormalizationForm_D))) {
        commands.erase(commands.find(name.normalized(QString::NormalizationForm_D)));
    }
}

void server::CommandExecutor::registerCommand(QString name,
                                              bool (CommandExecutor::* executable)(
                                                      const QStringList&)) {
    commands.insert(name.normalized(QString::NormalizationForm_D), executable);
}

void server::CommandExecutor::registerCommands() {
    // test command
    registerCommand("test", &CommandExecutor::testCommand);
    // change_speed_command <object_id> <new_speed>
    registerCommand("change_speed", &CommandExecutor::changeSpeedCommand);
}

// change_speed_command <object_id> <new_speed>
bool server::CommandExecutor::changeSpeedCommand(const QStringList& arguments) {
    // check for arguments count
    if (arguments.size() != 2) {
        return false;
    }

    // check if arguments are numbers
    bool status = true;
    qint64 objectId = arguments[0].toLongLong(&status);
    if (!status) {
        return false;
    }

    int newSpeed = arguments[1].toInt(&status);
    if (!status) {
        return false;
    }

    // check if object exists
    if (!gameWorld->getObjects().contains(objectId)) {

        return false;
    }

    auto* movingObject = dynamic_cast<core::Moving*>(gameWorld->getObjects()[objectId]);
    // check of object is moving.
    if (!movingObject) {
        return false;
    }

    // check for permission, NOT READY YET
    if (newSpeed < 0 && newSpeed > movingObject->getMaxSpeed()) {
        return false;
    }
    movingObject->setSpeed(newSpeed);
    return true;
}

//test command
bool server::CommandExecutor::testCommand(const QStringList& arguments) {
    for (QString argument : arguments) {
        qDebug() << argument;
    }
    return true;
}


