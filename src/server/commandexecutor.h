#ifndef COMMANDEXECUTOR_H
#define COMMANDEXECUTOR_H

#include <functional>

#include <QMap>
#include <QStringList>
#include <QString>

#include "../core/command.h"
#include "../core/gameworld.h"
#include "controllers/gameworldcontroller.h"

namespace server {

class CommandExecutor {
  public:
    explicit CommandExecutor(
            std::shared_ptr<server::GameWorldController> gameWorldController = nullptr);

    bool executeCommand(const core::Command& command);

    void
    registerCommand(const QString& name, bool (CommandExecutor::* executable)(const QStringList&));

    void unregisterCommand(const QString& name);

    void registerCommands();

    std::shared_ptr<core::GameWorld> getGameWorld();

  private:
    // key - command name, value - function
    // (takes command arguments, returns status: true - success, false - invalid syntax/ denied)
    QHash<QString, bool (CommandExecutor::*)(const QStringList&)> commands;

    std::shared_ptr<server::GameWorldController> gameWorldController;

    bool testCommand(const QStringList& arguments);

    bool changeSpeedCommand(const QStringList& arguments);

    bool changeMoveTargetCommand(const QStringList& arguments);
};

}


#endif //COMMANDEXECUTOR_H
