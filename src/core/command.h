#ifndef COMMAND_H
#define COMMAND_H

#include <QString>
#include <QStringList>

namespace core {

class Command {
  public:
    Command() = default;

    explicit Command(const QString& name, const QStringList& arguments = QStringList());

    const QString& getName() const;

    void setName(const QString& name);

    const QStringList& getArguments() const;

    void setArguments(const QStringList& arguments);

    static Command fromCommandLine(const QString& text);

  private:
    QString name;
    QStringList arguments;
};

}  // namespace core

#endif  // COMMAND_H
