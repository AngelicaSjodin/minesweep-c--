#include <iostream>
#include <string>
#include "game.h"
#include <limits>

int main() {
    std::cout << "____Minesweeper____\n";

    int rows = 0, cols = 0, mines = -1;
    std::string name;

    // Läs in rader och kolumner
    std::cout << "Amount of rows: ";
    if (!(std::cin >> rows) || rows <= 0) {
        std::cerr << "invalid amount of rows.\n";
        return 1;
    }

    std::cout << "amount of columns: ";
    if (!(std::cin >> cols) || cols <= 0) {
        std::cerr << "invalid amount of columns.\n";
        return 1;
    }

    // Läs in minor
    std::cout << "amount of bombs: ";
    if (!(std::cin >> mines) || mines < 0) {
        std::cerr << "invalid amount of bombs.\n";
        return 1;
    }

    if (mines >= rows * cols) {
        std::cerr << "Too many bombs!: must be less than rows*columns.\n";
        return 1;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Player name: ";
    std::getline(std::cin, name);
    if (name.empty()) name = "Player";

    try {
        Game game(rows, cols, mines, name);
        game.loop();
    } catch (const std::exception &e) {
        std::cerr << "error: " << e.what() << "\n";
        return 1;
    }

    std::cout << "Thank u for playing!\n";
    return 0;
}