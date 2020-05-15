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

    const QString& getAddress() const;

    int getPort() const;

    const std::shared_ptr<server::Engine>& getEngine() const;

    const std::shared_ptr<server::Server>& getServer() const;

  private:
    void onPaused() override;

    void onResumed() override;

    void constructInterface();

    void startServer();

    void connect();

    void joinGame();

    QString address;
    int port;

    std::shared_ptr<core::GameWorld> gameWorld = nullptr;

    std::shared_ptr<server::Engine> engine = nullptr;
    std::shared_ptr<server::Server> server = nullptr;
};

}

#endif  // OPTIONS_SCREEN_H
