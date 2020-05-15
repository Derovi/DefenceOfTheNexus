#ifndef CONNECTION_SCREEN_H
#define CONNECTION_SCREEN_H

#include <QPushButton>

#include "../screen.h"
#include "../../server/engine.h"
#include "../../server/network/server.h"

namespace client {

class ConnectionScreen : public Screen {
  public:
    ConnectionScreen();

  private:
    void onPaused() override;

    void onResumed() override;

    std::shared_ptr<server::Engine> engine;
    std::shared_ptr<server::Server> server;
};

}

#endif  // OPTIONS_SCREEN_H
