#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "cell.h"



class Board {
private:
    int rows, cols, bombs;                  
    std::vector<std::vector<Cell>> grid; 

    bool boardBorder(int r, int c) const;  
    void placeBombs();                  
    void determineAdjacency();           
    void fill(int r, int c);       

public:
    Board(int r, int c, int m);

    int reveal(int r, int c);
    bool toggleFlag(int r, int c);      
    bool allSafeRevealed() const;       
    void revealAllBombs();
    void print(bool showCoords = true) const; 
};

#endif