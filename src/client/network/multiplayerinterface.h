#ifndef MULTIPLAYERINTERFACE_H
#define MULTIPLAYERINTERFACE_H

typedef mbstate_t state;

#include <memory>

#include <QtCore/QObject>
#include <QtNetwork/QUdpSocket>
#include <QtCore/QQueue>

#include "../../core/command.h"
#include "../../core/gameworld.h"
#include "../../core/event.h"

namespace client {

class MultiplayerInterface : public QObject {
  Q_OBJECT
  public:
    enum State {
        STARTING_SERVER, CONNECTING_SERVER, CHOOSING_TEAM, IN_GAME,
    };

    MultiplayerInterface(QString address, int port, State state = STARTING_SERVER);

    void sendConnectRequest();

    void sendInitRequest();

    void sendCommand(const core::Command& command);

    void sendMessage(const QString& message);

    void eventReceived(const QString& message);

    void requestNickname(const QString& nickname);

    void requestSlot(uint8_t slot);

    const QString& getAddress() const;

    int getPort() const;

    const std::shared_ptr<QUdpSocket>& getSocket() const;

    const std::shared_ptr<core::GameWorld>& getGameWorld() const;

    uint8_t getTeam() const;

    QQueue<core::Event>& getEventQueue();

    bool isReady();

    State getState() const;

    void setTeam(uint8_t team);

    int getPlayerId() const;

    ~MultiplayerInterface() override {
        //qDebug() << "delete mult";
    };

  private:
    QString address;
    int port;
    QQueue<core::Event> eventQueue;

    std::shared_ptr<QUdpSocket> socket = nullptr;

    std::shared_ptr<core::GameWorld> gameWorld = nullptr;
    uint8_t team;

    void initResponse(const QString& message);
    void connectResponse(const QString& message);
    void worldUpdate(const QString& message);
    void nickNameResponse(const QString& message);
    void teamUpdate(const QString& message);

    void buildDatagrams();

    // datagram id, <datagram parts, start time>
    QMap<int, std::pair<QVector<QString>, QDateTime>> datagrams;

    const int timeout = 5000;
    State state;
    int playerId;

  private slots:

    void readMessage();

  signals:

    void inited();
    void connected(int teamCount);
    void nicknameUpdated(QString name);
    void slotsUpdated(QVector<QString> updated);
};

}

#endif  //MULTIPLAYERINTERFACE_H
