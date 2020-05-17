#include "aiplayer.h"

server::AIPlayer::AIPlayer(Engine* engine, int team = 0) : engine(engine), team(team) {}

int server::AIPlayer::getTeam() const {
    return team;
}

void server::AIPlayer::setTeam(int team) {
    AIPlayer::team = team;
}
