#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include "../screen.h"
#include "../../server/engine.h"
#include "../widgets/gamemap.h"
#include "../widgets/gameinterface.h"

namespace client {

class GameScreen : public Screen {
  public:
    GameScreen(const std::shared_ptr<core::GameWorld>& savedGameWorld = nullptr);

    ~GameScreen() override;

    const std::shared_ptr<server::Engine>& getEngine() const;

    GameMap* getGameMap() const;

    void draw() override;

    GameInterface* getInterface() const;

    uint8_t getTeam() const;

    void setTeam(uint8_t team);

  private:
    void onPaused() override;

    void onResumed() override;

    std::shared_ptr<server::Engine> engine;

    GameInterface* interface;

    GameMap* gameMap;

    uint8_t team;

    bool paused;
};

}

#endif //GAMESCREEN_H
