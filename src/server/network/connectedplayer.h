#ifndef CONNECTEDPLAYER_H
#define CONNECTEDPLAYER_H


#include <QtCore/QString>

namespace server {

class ConnectedPlayer {
  public:
    ConnectedPlayer(const QString& address, int port, int team);

    const QString& getAddress() const;

    void setAddress(const QString& address);

    int getPort() const;

    void setPort(int port);

    int getTeam() const;

    void setTeam(int team);

  private:
    QString address;
    int port;

    int team;
};

}

#endif //CONNECTEDPLAYER_H
