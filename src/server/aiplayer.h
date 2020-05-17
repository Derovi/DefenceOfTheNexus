#ifndef AIPLAYER_H
#define AIPLAYER_H

namespace server {

class Engine;

class AIPlayer {
  public:
    explicit AIPlayer(Engine* engine, int team);

    virtual void tick(int deltaTime) = 0;

    int getTeam() const;

    void setTeam(int team);

  protected:
    Engine* engine;
    int team;
};

}

#endif //AIPLAYER_H
