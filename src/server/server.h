#ifndef SERVER_H
#define SERVER_H

#include <QQueue>

#include "../utils/queue.h"
#include "../core/command.h"

namespace server {

class Server {
  public:
    std::shared_ptr<Queue<core::Command>> getCommandQueue();

    void registerCommandQueue(std::shared_ptr<Queue<core::Command>> commandQueue);

    void start();

    void finish();

  private:
    std::shared_ptr<Queue<core::Command>> commandQueue;
};

}  // namespace server


#endif  // SERVER_H
