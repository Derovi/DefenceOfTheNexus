#include "connectedplayer.h"

server::ConnectedPlayer::ConnectedPlayer(const QString& address, int port, int team):
        address(address), port(port), team(team) {}

const QString& server::ConnectedPlayer::getAddress() const {
    return address;
}

void server::ConnectedPlayer::setAddress(const QString& address) {
    ConnectedPlayer::address = address;
}

int server::ConnectedPlayer::getPort() const {
    return port;
}

void server::ConnectedPlayer::setPort(int port) {
    ConnectedPlayer::port = port;
}

int server::ConnectedPlayer::getTeam() const {
    return team;
}

void server::ConnectedPlayer::setTeam(int team) {
    ConnectedPlayer::team = team;
}
