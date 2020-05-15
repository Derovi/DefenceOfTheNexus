#ifndef MULTIPLAYERINTERFACE_H
#define MULTIPLAYERINTERFACE_H

#include <memory>

#include <QtCore/QObject>
#include <QtNetwork/QUdpSocket>

#include "../../core/command.h"

class MultiplayerInterface : public QObject {
  Q_OBJECT
  public:
    MultiplayerInterface(QString address, QString port);

    void sendCommand(const core::Command& command);

    void sendMessage(const QString& message);

    void readMessage();

    const QString& getAddress() const;

    const QString& getPort() const;

    const std::shared_ptr<QUdpSocket>& getSocket() const;

  private:
    QString address;
    QString port;

    std::shared_ptr<QUdpSocket> socket = nullptr;
};

#endif  //MULTIPLAYERINTERFACE_H
