#ifndef COMMAND_H
#define COMMAND_H

#include <QString>
#include <QStringList>

namespace core {

class Command {
  public:
    Command() = default;

    explicit Command(const QString& name);

    const QString& getName() const;

    void setName(const QString& name);

    const QStringList& getArguments() const;

    void setArguments(const QStringList& arguments);

    static Command fromCommandLine(QString text);

  private:
    QString name;
    QStringList arguments;
};

}

#endif //COMMAND_H
