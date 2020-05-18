#ifndef GAMECREATIONSCREEN_H
#define GAMECREATIONSCREEN_H

#include <QPushButton>

#include "../screen.h"
#include "../network/multiplayerinterface.h"
#include "../../server/engine.h"
#include "../../server/network/server.h"

namespace client {

class GameCreationScreen : public Screen {
  public:
    GameCreationScreen();

    const std::shared_ptr<MultiplayerInterface>& getMultiplayerInterface() const;

  private:
    void onPaused() override;

    void onResumed() override;

    void startServer();

    std::shared_ptr<server::Engine> engine = nullptr;
    std::shared_ptr<server::Server> server = nullptr;

    std::shared_ptr<MultiplayerInterface> multiplayerInterface;

    uint8_t getPlayerCount() { return 3; }

    uint8_t getMyPlayerId();
};

}

#endif //GAMECREATIONSCREEN_H