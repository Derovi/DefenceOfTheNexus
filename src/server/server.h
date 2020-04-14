#ifndef SERVER_H
#define SERVER_H

#include <QQueue>

#include "../core/command.h"

namespace server {

class Server {
  public:
    std::shared_ptr<QQueue<core::Command>> getCommandQueue();

    void registerCommandQueue(std::shared_ptr<QQueue<core::Command>> commandQueue);

    void start();

    void finish();

  private:
    std::shared_ptr<QQueue<core::Command>> commandQueue;
};

}


#endif //SERVER_H
