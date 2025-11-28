#ifndef GAME_H
#define GAME_H

#include <memory>
#include "board.h"
#include "player.h"
#include "inputhandler.h"

class Game {
private:
    std::unique_ptr<Board> board;
    std::unique_ptr<Player> player;
    InputHandler inputHandler;
    bool gameOver = false;

public:
    Game(int rows, int cols, int mines, const std::string &playerName);
    void loop();
};

#endif