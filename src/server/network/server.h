#ifndef SERVER_H
#define SERVER_H

#include <QQueue>
#include <QtNetwork/QUdpSocket>

#include "../../utils/queue.h"
#include "../../core/command.h"
#include "connectedplayer.h"
#include "../engine.h"

namespace server {

class Server : public QObject {
  Q_OBJECT
  public:
    Server(Engine* engine, int port);

    std::shared_ptr<Queue<core::Command>> getCommandQueue();

    void registerCommandQueue(std::shared_ptr<Queue<core::Command>> commandQueue);

    void start();

    void finish();

    void readMessage();

    void sendMessage(const ConnectedPlayer& connectedPlayer, const QString& message);

    void updateGameWorld();

    void initPlayer(const QString& address, int port);

    void commandReceived(const QString& address, int port, const QString& message);

    int getPort() const;

    Engine* getEngine() const;

    const std::shared_ptr<QUdpSocket>& getSocket() const;

  private:
    QVector<ConnectedPlayer> connectedPlayers;

    std::shared_ptr<Queue<core::Command>> commandQueue;

    std::shared_ptr<QUdpSocket> socket = nullptr;

    Engine* engine;

    int port;
};

}  // namespace server


#endif  // SERVER_H
