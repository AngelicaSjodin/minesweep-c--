#include "player.h"

Player::Player(const std::string &n) : name(n), moves(0), flagsPlaced(0) {}

const std::string &Player::getName() const {
    return name;
}

int Player::getMoves() const {
    return moves;
}

int Player::getFlags() const {
    return flagsPlaced;
}

void Player::incrementMoves() {
    moves++;
}

void Player::incrementFlags() {
    flagsPlaced++;
}

void Player::decrementFlags() {
    if (flagsPlaced > 0) flagsPlaced--;
}