#include "cell.h"

#include "cell.h"
//implementering
Cell::Cell() : bomb(false), revealed(false), flagged(false), adjacent(0) {}

bool Cell::isBomb() const { return bomb; }
bool Cell::isRevealed() const { return revealed; }
bool Cell::isFlagged() const { return flagged; }
int Cell::adjacentBombs() const { return adjacent; }

void Cell::setBomb(bool v) { bomb = v; }
void Cell::setRevealed(bool v) { revealed = v; }
void Cell::setFlagged(bool v) { flagged = v; }
void Cell::setAdjacent(int n) { adjacent = n; }