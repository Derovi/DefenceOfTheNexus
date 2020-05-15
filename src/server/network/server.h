#ifndef SERVER_H
#define SERVER_H

#include <QQueue>
#include <QtNetwork/QUdpSocket>

#include "../../utils/queue.h"
#include "../../core/command.h"

namespace server {

class Server {
  public:
    Server(const QString& port);

    std::shared_ptr<Queue<core::Command>> getCommandQueue();

    void registerCommandQueue(std::shared_ptr<Queue<core::Command>> commandQueue);

    void start();

    void finish();

  private:
    std::shared_ptr<Queue<core::Command>> commandQueue;

    std::shared_ptr<QUdpSocket> socket = nullptr;
};

}  // namespace server


#endif  // SERVER_H
