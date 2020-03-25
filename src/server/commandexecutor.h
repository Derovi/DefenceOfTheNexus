//
// Created by derovi on 3/24/2020.
//

#ifndef COMMANDEXECUTOR_H
#define COMMANDEXECUTOR_H

#include <QMap>
#include <functional>
#include <QStringList>
#include <QString>
#include "../core/command.h"
#include "../core/gameworld.h"

namespace server {

class CommandExecutor {
  public:
    CommandExecutor();

    explicit CommandExecutor(core::GameWorld * gameWorld);

    bool executeCommand(const core::Command& command);

    void registerCommand(QString name, std::function<bool(QStringList)> executable);

    void unregisterCommand(QString name);

  private:
    // key - command name, value - function
    // (takes command arguments, returns status: true - success, false - invalid syntax/ denied)
    QMap<QString, std::function<bool(QStringList)>> commands;

    core::GameWorld * gameWorld;

    static bool testCommand(QStringList arguments);
};

}


#endif //COMMANDEXECUTOR_H
