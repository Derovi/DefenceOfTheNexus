#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include "../screen.h"
#include "../../server/engine.h"
#include "../widgets/gamemap.h"

namespace client {

class GameScreen : public Screen {
  public:
    GameScreen(const std::shared_ptr<core::GameWorld>& savedGameWorld = nullptr);

    ~GameScreen() override;

    const std::shared_ptr<server::Engine>& getEngine() const;

    GameMap* getGameMap() const;

  private:
    void onPaused() override;

    void onResumed() override;

    bool paused;

    std::shared_ptr<server::Engine> engine;

    GameMap* gameMap;
};

}

#endif //GAMESCREEN_H
