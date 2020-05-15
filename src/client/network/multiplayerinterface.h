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
    MultiplayerInterface(GameScreen* gameScreen, QString address, int port);

    void sendInitRequest();

    void sendCommand(const core::Command& command);

    void sendMessage(const QString& message);

    void readMessage();

    const QString& getAddress() const;

    int getPort() const;

    const std::shared_ptr<QUdpSocket>& getSocket() const;

    GameScreen* getGameScreen() const;

    void setGameScreen(GameScreen* gameScreen);

  private:
    QString address;
    int port;

    std::shared_ptr<QUdpSocket> socket = nullptr;

    GameScreen* gameScreen;

    void initResponse(const QString& message);

    void worldUpdate(const QString& message);
};

}

#endif  //MULTIPLAYERINTERFACE_H
