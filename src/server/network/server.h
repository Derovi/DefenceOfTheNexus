#ifndef SERVER_H
#define SERVER_H

#include <QQueue>
#include <QtNetwork/QUdpSocket>

#include "../../utils/queue.h"
#include "../../core/command.h"

namespace server {

class Server : public QObject {
  Q_OBJECT
  public:
    Server(int port);

    std::shared_ptr<Queue<core::Command>> getCommandQueue();

    void registerCommandQueue(std::shared_ptr<Queue<core::Command>> commandQueue);

    void start();

    void finish();

    void readMessage();

    void sendMessage(const QString& message);

    int getPort() const;

  private:
    std::shared_ptr<Queue<core::Command>> commandQueue;

    std::shared_ptr<QUdpSocket> socket = nullptr;

    int port;
};

}  // namespace server


#endif  // SERVER_H
