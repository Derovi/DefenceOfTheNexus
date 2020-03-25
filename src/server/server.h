//
// Created by derovi on 3/25/2020.
//

#ifndef SERVER_H
#define SERVER_H

#include <QQueue>
#include "../core/command.h"

namespace server {

class Server {
  public:
    QQueue<core::Command>* getCommandQueue() const;

    void registerCommandQueue(QQueue<core::Command>* commandQueue);

    void start();

    void finish();

  private:
    QQueue<core::Command> * commandQueue;
};

}


#endif //SERVER_H
