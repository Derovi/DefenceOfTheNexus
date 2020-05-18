#include "connectedplayer.h"

#include <utility>

server::ConnectedPlayer::ConnectedPlayer(QString address, int port, int team, uint8_t id):
        address(std::move(address)), port(port), team(team), id(id),
        nickname("Player" + QString::number(id)) {}

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

uint8_t server::ConnectedPlayer::getId() const {
    return id;
}

const QString& server::ConnectedPlayer::getNickname() const {
    return nickname;
}

void server::ConnectedPlayer::setNickname(const QString& nickname) {
    ConnectedPlayer::nickname = nickname;
}
