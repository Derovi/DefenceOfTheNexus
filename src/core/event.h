#ifndef EVENT_H
#define EVENT_H

#include <QtCore/QString>
#include <QtCore/QPoint>
#include <QtCore/QStringList>

namespace core {

class Event {
  public:
    enum Type {
        HIT_EVENT, // arguments: <UNIT_ID>
        DIE_EVENT, // arguments: <UNIT_ID>
        MAIN_MUSIC_EVENT // arguments <URL_MUSIC>
    };

    Event() = default;

    Event(Type type, QStringList arguments);

    Type getType() const;

    void setType(Type type);

    const QStringList& getArguments() const;

    void setArguments(const QStringList& arguments);

  private:
    Type type;
    QStringList arguments;
};

}

#endif //EVENT_H
