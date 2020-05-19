#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include "../screen.h"
#include "../../server/engine.h"
#include "../widgets/gamemap.h"
#include "../widgets/gameinterface.h"
#include "../network/multiplayerinterface.h"

namespace client {

class GameScreen : public Screen {
  public:
    explicit GameScreen(const std::shared_ptr<MultiplayerInterface>& multiplayerInterface);

    ~GameScreen() override;

    const std::shared_ptr<server::Engine>& getEngine() const;

    GameMap* getGameMap() const;

    void draw() override;

    GameInterface* getInterface() const;

    uint8_t getTeam() const;

    const std::shared_ptr<MultiplayerInterface>& getMultiplayerInterface() const;

    void setTeam(uint8_t team);

  private:
    void onPaused() override;

    void onResumed() override;

    std::shared_ptr<MultiplayerInterface> multiplayerInterface;

    std::shared_ptr<server::Engine> engine;

    GameInterface* interface;

    ImageButton* teamButton;

    GameMap* gameMap;

    bool paused;
};

}

#endif //GAMESCREEN_H
