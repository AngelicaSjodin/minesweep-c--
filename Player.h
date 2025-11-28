#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
private:
    std::string name;
    int moves;
    int flagsPlaced;

public:
    Player(const std::string &n);

    const std::string &getName() const;
    int getMoves() const;
    int getFlags() const;
    void incrementMoves();
    void incrementFlags();
    void decrementFlags();
};

#endif