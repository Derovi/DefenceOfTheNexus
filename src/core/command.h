#ifndef COMMAND_H
#define COMMAND_H

#include <QString>
#include <QStringList>

namespace core {

class Command {
  public:
    Command();

    explicit Command(QString name);

    const QString& getName() const;

    void setName(const QString& name);

    const QStringList& getArguments() const;

    void setArguments(const QStringList& arguments);

    static Command getCommand(QString text);

  private:
    QString name;
    QStringList arguments;
};

}

#endif //COMMAND_H
