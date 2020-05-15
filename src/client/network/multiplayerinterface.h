#ifndef MULTIPLAYERINTERFACE_H
#define MULTIPLAYERINTERFACE_H

#include <memory>

#include <QtCore/QObject>
#include <QtNetwork/QUdpSocket>

#include "../../core/command.h"

class MultiplayerInterface : public QObject {
  Q_OBJECT
  public:
    MultiplayerInterface();

    void sendCommand(const core::Command& command);

    void sendMessage(const QString& message);

    void readMessage();

  private:
    std::shared_ptr<QUdpSocket> socket = nullptr;
};

#endif  //MULTIPLAYERINTERFACE_H
