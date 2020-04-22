#include <memory>
#include <QDebug>

#include "../core/gameworld.h"
#include "../core/attributes/moving.h"

#include "commandexecutor.h"

server::CommandExecutor::CommandExecutor(std::shared_ptr<core::GameWorld> gameWorld):
        gameWorld(gameWorld) {
    registerCommands();
}


bool server::CommandExecutor::executeCommand(const core::Command& command) {
    if (!commands.contains(command.getName())) {
        return false;
    }
    return (this->*commands[command.getName()])(
            command.getArguments());
}

void server::CommandExecutor::unregisterCommand(const QString& name) {
    commands.remove(name);
}

void server::CommandExecutor::registerCommand(const QString& name,
                                              bool (CommandExecutor::* executable)(
                                                      const QStringList&)) {
    commands.insert(name, executable);
}

void server::CommandExecutor::registerCommands() {
    // test command
    registerCommand("test", &CommandExecutor::testCommand);
    // change_speed_command <object_id> <new_speed>
    registerCommand("change_speed", &CommandExecutor::changeSpeedCommand);
    registerCommand("change_move_target", &CommandExecutor::changeMoveTargetCommand);
    registerCommand("mine_resource", &CommandExecutor::mineResource);
}

// change_speed_command <object_id> <new_speed>
bool server::CommandExecutor::changeSpeedCommand(const QStringList& arguments) {
    // check for arguments count
    if (arguments.size() != 2) {
        return false;
    }

    // check if arguments are numbers
    bool status = true;
    int64_t objectId = arguments[0].toLongLong(&status);
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

    if (!gameWorld->getObjects()[objectId]->hasAttribute("moving")) {
        return false;
    }

    std::shared_ptr<core::Moving> moving = std::dynamic_pointer_cast<core::Moving>(
            gameWorld->getObjects()[objectId]->getAttribute("moving"));

    // check of object is moving.
    if (!moving) {
        return false;
    }

    // check for permission, NOT READY YET
    if (newSpeed < 0 && newSpeed > moving->getMaxSpeed()) {
        return false;
    }
    moving->setSpeed(newSpeed);
    return true;
}

// change_speed_command <object_id> <x> <y>
bool server::CommandExecutor::changeMoveTargetCommand(const QStringList& arguments) {
    // check for arguments count
    if (arguments.size() != 3) {
        return false;
    }

    // check if arguments are numbers
    bool status = true;
    int64_t objectId = arguments[0].toLongLong(&status);
    if (!status) {
        return false;
    }

    int x = arguments[1].toInt(&status);
    if (!status) {
        return false;
    }

    int y = arguments[2].toInt(&status);
    if (!status) {
        return false;
    }

    // check if object exists
    if (!gameWorld->getObjects().contains(objectId)) {
        return false;
    }

    auto object = gameWorld->getObjects()[objectId];

    if (!object->hasAttribute("moving")) {
        return false;
    }

    std::shared_ptr<core::Moving> moving = std::dynamic_pointer_cast<core::Moving>(
            object->getAttribute("moving"));

    // check of object is moving.
    if (!moving) {
        return false;
    }

    // check for permission, NOT READY YET
    moving->setDirection(QVector2D(x - object->getPosition().x(), y - object->getPosition().y()));
    return true;
}


//test command
bool server::CommandExecutor::testCommand(const QStringList& arguments) {
    for (QString argument : arguments) {
        qDebug() << argument;
    }
    return true;
}

bool server::CommandExecutor::mineResource(const QStringList& arguments) {
    return false;
}



