#include <memory>

#include <QDebug>

#include "../core/gameworld.h"
#include "../core/attributes/moving.h"

#include "commandexecutor.h"
#include "../utils/factory.h"

server::CommandExecutor::CommandExecutor(
        std::shared_ptr<server::GameWorldController> gameWorldController):
        gameWorldController(gameWorldController) {
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
    registerCommand("change_speed", &CommandExecutor::changeSpeedCommand);
    registerCommand("change_move_target", &CommandExecutor::changeMoveTargetCommand);
    registerCommand("mine_resource", &CommandExecutor::mineResource);
    registerCommand("attack", &CommandExecutor::attackCommand);
    registerCommand("build", &CommandExecutor::buildCommand);
    registerCommand("buildWall", &CommandExecutor::buildWallCommand);
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
    if (!getGameWorld()->getObjects().contains(objectId)) {

        return false;
    }

    if (!getGameWorld()->getObjects()[objectId]->hasAttribute("moving")) {
        return false;
    }

    std::shared_ptr<core::Moving> moving = std::dynamic_pointer_cast<core::Moving>(
            getGameWorld()->getObjects()[objectId]->getAttribute("moving"));

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
    if (!getGameWorld()->getObjects().contains(objectId)) {
        return false;
    }

    auto object = getGameWorld()->getObjects()[objectId];

    if (!object->hasAttribute("moving")) {
        return false;
    }

    std::shared_ptr<core::Moving> moving = std::dynamic_pointer_cast<core::Moving>(
            object->getAttribute("moving"));

    // check of object is moving.
    if (!moving) {
        return false;
    }

    gameWorldController->getControllers()[objectId]->cancelTargets();

    // check for permission, NOT READY YET
    //moving->setDirection(QVector2D(x - object->getPosition().x(), y - object->getPosition().y()));
    qDebug() << "click command!";
    DataBundle bundle;
    auto point = std::make_shared<QPointF>(x, y);
    bundle.registerVariable("destinationPoint", point);
    gameWorldController->getControllers()[objectId]->linkStrategies(bundle);
    return true;
}


//test command
bool server::CommandExecutor::testCommand(const QStringList& arguments) {
    for (QString argument : arguments) {
        qDebug() << argument;
    }
    return true;
}

// mine_resource <miner id> <target id>
bool server::CommandExecutor::mineResource(const QStringList& arguments) {
    if (arguments.size() != 2) {
        return false;
    }
    bool isOk = true;
    uint64_t minerId = arguments[0].toInt(&isOk);
    if (!isOk) {
        return false;
    }

    uint64_t resourceId = arguments[1].toInt(&isOk);
    if (!isOk) {
        return false;
    }

    auto miner = getGameWorld()->getObjects().find(minerId);
    if (miner == getGameWorld()->getObjects().end()
        || !miner.value()->hasAttribute("mining")) {
        return false;
    }

    auto target = getGameWorld()->getObjects().find(resourceId);
    if (target == getGameWorld()->getObjects().end()
        || !target.value()->hasAttribute("resource")) {
        return false;
    }

    gameWorldController->getControllers()[minerId]->cancelTargets();
    qDebug() << minerId << " wanna mine " << resourceId << endl;

    auto destPoint = std::make_shared<QPointF>(target.value()->getPosition());

    DataBundle bundle;
    bundle.registerVariable("miningTarget", target.value());
    bundle.registerVariable("destinationPoint", destPoint);
    gameWorldController->getControllers()[minerId]->linkStrategies(bundle);
    return true;
}

// mine_resource <miner id> <target id>
bool server::CommandExecutor::buildCommand(const QStringList& arguments) {
    qDebug() << "build command h";
    int team = arguments[0].toInt();
    QString type = arguments[1];
    QPoint position = QPoint(arguments[2].toInt(), arguments[3].toInt());
    getGameWorld()->build(utils::Factory::getObjectSignature(type).value(), position, team);
    return true;
}

// mine_resource <miner id> <target id>
bool server::CommandExecutor::buildWallCommand(const QStringList& arguments) {
    qDebug() << "build wall command h";
    int team = arguments[0].toInt();
    QString type = arguments[1];
    QPoint pos1 = QPoint(arguments[2].toInt(), arguments[3].toInt());
    QPoint pos2 = QPoint(arguments[4].toInt(), arguments[5].toInt());
    getGameWorld()->buildWall(pos1, pos2, utils::Factory::getObjectSignature(type).value(),
                              utils::Factory::getObjectSignature("column1").value(), team);
    return true;
}

// attack <attacker id> <target id>
bool server::CommandExecutor::attackCommand(const QStringList& arguments) {
    if (arguments.size() != 2) {
        return false;
    }
    bool isOk = true;
    uint64_t attackerId = arguments[0].toInt(&isOk);
    if (!isOk) {
        return false;
    }

    uint64_t targetId = arguments[1].toInt(&isOk);
    if (!isOk) {
        return false;
    }

    auto attacker = getGameWorld()->getObjects().find(attackerId);
    if (attacker == getGameWorld()->getObjects().end()
        || !attacker.value()->hasAttribute("damaging")) {
        return false;
    }

    auto target = getGameWorld()->getObjects().find(targetId);
    if (target == getGameWorld()->getObjects().end()
        || !target.value()->hasAttribute("damageable")) {
        return false;
    }

    if (!getGameWorld()->areEnemies((**attacker).getTeam(), (**target).getTeam())) {
        return false;
    }

    gameWorldController->getControllers()[attackerId]->cancelTargets();
    qDebug() << attackerId << " wanna attack " << targetId << endl;

    auto destPoint = std::make_shared<QPointF>(target.value()->getPosition());

    DataBundle bundle;
    bundle.registerVariable("attackTarget", target.value());
    bundle.registerVariable("destinationPoint", destPoint);
    gameWorldController->getControllers()[attackerId]->linkStrategies(bundle);
    return true;
}

std::shared_ptr<core::GameWorld> server::CommandExecutor::getGameWorld() {
    return gameWorldController->getGameWorld();
}
