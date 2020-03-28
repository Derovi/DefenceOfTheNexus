#ifndef COMMANDEXECUTOR_H
#define COMMANDEXECUTOR_H

#include <functional>

#include <QMap>
#include <QStringList>
#include <QString>

#include "../core/command.h"
#include "../core/gameworld.h"

namespace server {

class CommandExecutor {
  public:
    explicit CommandExecutor(core::GameWorld* gameWorld = nullptr);

    bool executeCommand(const core::Command& command);

    void registerCommand(const QString& name, bool (CommandExecutor::* executable)(const QStringList&));

    void unregisterCommand(const QString& name);

    void registerCommands();

  private:
    // key - command name, value - function
    // (takes command arguments, returns status: true - success, false - invalid syntax/ denied)
    QHash<QString, bool (CommandExecutor::*)(const QStringList&)> commands;

    core::GameWorld* gameWorld;

    bool testCommand(const QStringList& arguments);

    bool changeSpeedCommand(const QStringList& arguments);
};

}


#endif //COMMANDEXECUTOR_H
