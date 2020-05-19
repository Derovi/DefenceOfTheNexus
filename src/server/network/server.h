#ifndef SERVER_H
#define SERVER_H

#include <QQueue>
#include <QMediaPlayer>
#include <QtNetwork/QUdpSocket>

#include "../../utils/queue.h"
#include "../../core/command.h"
#include "../engine.h"

#include "connectedplayer.h"

namespace server {

class Server : public QObject {
  Q_OBJECT

  public:
    Server(Engine* engine, int port);

    std::shared_ptr<Queue<core::Command>> getCommandQueue();

    void registerCommandQueue(std::shared_ptr<Queue<core::Command>> commandQueue);

    void start();

    void finish();

    void updateGameWorld(QVector<core::Event> events);

    void sendMessage(const ConnectedPlayer& connectedPlayer, const QString& message);

    void initPlayer(uint8_t playerId);

    void nickNameRequest(uint8_t playerId, const QString& message);

    void slotRequest(uint8_t playerId, const QString& message);

    uint8_t connectPlayer(const QString& address, int port);

    uint8_t getPlayerId(const QString& address, int port);

    ConnectedPlayer getConnectedPlayer(uint8_t id);

    void commandReceived(const QString& address, int port, const QString& message);

    int getPort() const;

    Engine* getEngine() const;

    const std::shared_ptr<QUdpSocket>& getSocket() const;

    int getCurrentDatagramId() const;

  private:
    QVector<ConnectedPlayer> connectedPlayers;

    std::shared_ptr<Queue<core::Command>> commandQueue;

    std::shared_ptr<QUdpSocket> socket = nullptr;

    Engine* engine;

    int port;

    int currentDatagramId;

    QVector<std::shared_ptr<QMediaPlayer> > musicPlayers;

    void playSound(QStringList arguments);

    void handleEvent(core::Event event);

  private slots:

    void readMessage();
};

}  // namespace server


#endif  // SERVER_H
