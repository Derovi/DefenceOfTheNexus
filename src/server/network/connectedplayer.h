#ifndef CONNECTEDPLAYER_H
#define CONNECTEDPLAYER_H


#include <QtCore/QString>

namespace server {

class ConnectedPlayer {
  public:
    ConnectedPlayer();

    ConnectedPlayer(QString  address, int port, int team, uint8_t id);

    const QString& getAddress() const;

    void setAddress(const QString& address);

    int getPort() const;

    void setPort(int port);

    int getTeam() const;

    void setTeam(int team);

    uint8_t getId() const;

    const QString& getNickname() const;

    void setNickname(const QString& nickname);

  private:
    QString nickname;
    QString address;
    int port{};
    uint8_t id{};

    int team{};
};

}

#endif //CONNECTEDPLAYER_H
