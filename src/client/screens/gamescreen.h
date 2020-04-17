#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include "../screen.h"
#include "../../server/engine.h"

namespace client {

class GameScreen : public Screen {
  public:
    GameScreen();

    ~GameScreen();

    const std::shared_ptr<server::Engine>& getEngine() const;

  private:
    void onPaused() override;

    void onResumed() override;

    std::shared_ptr<server::Engine> engine;
};

}

#endif //GAMESCREEN_H
