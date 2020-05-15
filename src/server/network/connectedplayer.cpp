#include "connectedplayer.h"

ConnectedPlayer::ConnectedPlayer(const QString& address, int port, int team):
        address(address), port(port), team(team) {}

const QString& ConnectedPlayer::getAddress() const {
    return address;
}

void ConnectedPlayer::setAddress(const QString& address) {
    ConnectedPlayer::address = address;
}

int ConnectedPlayer::getPort() const {
    return port;
}

void ConnectedPlayer::setPort(int port) {
    ConnectedPlayer::port = port;
}

int ConnectedPlayer::getTeam() const {
    return team;
}

void ConnectedPlayer::setTeam(int team) {
    ConnectedPlayer::team = team;
}
