#ifndef CELL_H
#define CELL_H

//statusen för varje ruta
class Cell {
private:
    bool bomb;
    bool revealed;
    bool flagged;
    int adjacent;

public:
    Cell(); // konstruktor

    bool isBomb() const;
    bool isRevealed() const;
    bool isFlagged() const;
    int adjacentBombs() const;

    void setBomb(bool v);
    void setRevealed(bool v);
    void setFlagged(bool v);
    void setAdjacent(int n);
};

#endif