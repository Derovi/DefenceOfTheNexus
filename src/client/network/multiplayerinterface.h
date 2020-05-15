#ifndef MULTIPLAYERINTERFACE_H
#define MULTIPLAYERINTERFACE_H

#include <memory>

#include <QtCore/QObject>
#include <QtNetwork/QUdpSocket>

#include "../../core/command.h"
#include "../screens/gamescreen.h"

namespace client {

class MultiplayerInterface : public QObject {
  Q_OBJECT
  public:
    MultiplayerInterface(QString address, int port);

    void sendInitRequest();

    void sendCommand(const core::Command& command);

    void sendMessage(const QString& message);

    const QString& getAddress() const;

    int getPort() const;

    const std::shared_ptr<QUdpSocket>& getSocket() const;

    GameScreen* getGameScreen() const;

    void setGameScreen(GameScreen* gameScreen);

    const std::shared_ptr<core::GameWorld>& getGameWorld() const;

    uint8_t getTeam() const;

    bool isReady();

  private:
    QString address;
    int port;

    std::shared_ptr<QUdpSocket> socket = nullptr;

    std::shared_ptr<core::GameWorld> gameWorld = nullptr;
    uint8_t team;

    void initResponse(const QString& message);
    void worldUpdate(const QString& message);

  private slots:
    void readMessage();
};

}

#endif  //MULTIPLAYERINTERFACE_H
