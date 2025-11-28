#include "game.h"
#include <iostream>
using namespace std;

Game::Game(int rows, int cols, int mines, const string &playerName) {
    board = make_unique<Board>(rows, cols, mines);
    player = make_unique<Player>(playerName);
}

void Game::loop() {
    while (!gameOver) {
        board->print();
        cout << "\n" << player->getName() << " | Moves: "
             << player->getMoves() << " | Flags: "
             << player->getFlags() << "\n";

        cout << "Commandon:";
        cout << "Choose square: r rownumber colnumber \n";
        cout << "Flag square: f rownumber colnumber\n";
        cout << "End game: q\n";
        cout << "What do u want to do?: ";

        string line;
        if (!getline(cin, line)) return; 

        auto cmd = inputHandler.parse(line);
        if (!cmd) {
            cout << "Invalid commando!\n";
            continue;
        }

        if (cmd->type == 'q') {
            cout << "Closing...\n";
            return;
        }

        int r = cmd->row - 1;
        int c = cmd->col - 1;

        if (cmd->type == 'r') {
            int result = board->reveal(r, c);
            if (result == 1) {
                cout << "\nYAY! U found a bomb!\n";
                board->revealAllBombs();
                board->print();
                gameOver = true;
                return;
            }
            if (result == -2) cout << "outside boards borders!\n";

            player->incrementMoves();

            if (board->allSafeRevealed()) {
                cout << "\nYOU WON!\n";
                board->revealAllBombs();
                board->print();
                gameOver = true;
                return;
            }

        } else if (cmd->type == 'f') {
            bool flagged = board->toggleFlag(r, c);
            if (flagged) player->incrementFlags();
            else player->decrementFlags();
        }
    }
}