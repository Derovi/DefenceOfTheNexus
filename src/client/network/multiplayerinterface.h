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
    MultiplayerInterface(QString address, QString port);

    void sendInitRequest();

    void sendCommand(const core::Command& command);

    void sendMessage(const QString& message);

    void readMessage();

    const QString& getAddress() const;

    const QString& getPort() const;

    const std::shared_ptr<QUdpSocket>& getSocket() const;

    const std::shared_ptr<GameScreen>& getGameScreen() const {
        return gameScreen;
    }

    void setGameScreen(const std::shared_ptr<GameScreen>& gameScreen) {
        MultiplayerInterface::gameScreen = gameScreen;
    }

  private:
    QString address;
    QString port;

    std::shared_ptr<GameScreen> gameScreen;

    std::shared_ptr<QUdpSocket> socket = nullptr;

    void initResponse(const QString& message);

    void worldUpdate(const QString& message);
};

}

#endif  //MULTIPLAYERINTERFACE_H
