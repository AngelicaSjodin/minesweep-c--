#include "board.h"
#include <iostream>
#include <queue>
#include <random>
#include <algorithm>
#include <numeric>
#include <iomanip>
using namespace std;

//coinstruktoren +grid
Board::Board(int r, int c, int m) : rows(r), cols(c), bombs(m) {
    grid.assign(rows, vector<Cell>(cols));
    placeBombs();
    determineAdjacency();
}

bool Board::boardBorder(int r, int c) const {
    return r >= 0 && r < rows && c >= 0 && c < cols;
}

void Board::placeBombs() {
    vector<int> idx(rows * cols); 
    iota(idx.begin(), idx.end(), 0);
    random_device rd;
    mt19937 g(rd()); 
    shuffle(idx.begin(), idx.end(), g);

    for (int i = 0; i < bombs; ++i) {
        int v = idx[i];
        int rr = v / cols;
        int cc = v % cols;
        grid[rr][cc].setBomb(true); 
    }
}

//hur många bomber som är nära varje ruta
void Board::determineAdjacency() {
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (grid[r][c].isBomb()) {
                grid[r][c].setAdjacent(-1); 
                continue;
            }
            int cnt = 0;
            for (int dr = -1; dr <= 1; ++dr)
                for (int dc = -1; dc <= 1; ++dc) {
                    if (dr == 0 && dc == 0) continue;
                    int nr = r + dr, nc = c + dc;
                    if (boardBorder(nr, nc) && grid[nr][nc].isBomb()) cnt++;
                }
            grid[r][c].setAdjacent(cnt);
        }
    }
}

//typ när man väljer en ruta
int Board::reveal(int r, int c) {
    if (!boardBorder(r, c)) return -2;     // utanför brädan

    Cell &cell = grid[r][c];
    if (cell.isRevealed() || cell.isFlagged()) return -1;//redan vald,flaggad

    cell.setRevealed(true);
    if (cell.isBomb()) return 1;                        // hitta bomb, game over

    if (cell.adjacentBombs() == 0) fill(r, c);// bomb fri
    return 0;
}

//fyller på, öppnar upp närliggande fria rutor
void Board::fill(int r, int c) {
    queue<pair<int,int>> q;
    q.push({r,c});
    while (!q.empty()) {
        auto [cr,cc] = q.front(); q.pop();
        for (int dr=-1; dr<=1; ++dr)
            for (int dc=-1; dc<=1; ++dc) {
                int nr = cr+dr, nc = cc+dc;
                if (!boardBorder(nr,nc)) continue;
                Cell &cell = grid[nr][nc];
                if (cell.isRevealed() || cell.isFlagged()) continue;
                cell.setRevealed(true);
                //+fria rutor bredvid fria rutor
                if (!cell.isBomb() && cell.adjacentBombs()==0)
                    q.push({nr,nc});
            }
    }
}

//placera eller ta bort flagga
bool Board::toggleFlag(int r, int c) {
    if (!boardBorder(r,c)) return false;
    Cell &cell = grid[r][c];
    if (cell.isRevealed()) return false; 
    bool newState = !cell.isFlagged();
    cell.setFlagged(newState);
    return newState;
}
//kollar om alla fria rutor är hittade = win :D
bool Board::allSafeRevealed() const {
    for (int r=0;r<rows;++r)
        for (int c=0;c<cols;++c)
            if (!grid[r][c].isBomb() && !grid[r][c].isRevealed())
                return false;
    return true;
}

//visar alla bomber när man förlorar
void Board::revealAllBombs() {
    for (int r=0;r<rows;++r)
        for (int c=0;c<cols;++c)
            if (grid[r][c].isBomb()) grid[r][c].setRevealed(true);
}
//skriver ut brädan
void Board::print(bool showCoords) const {
    //kolumn nummer
    if (showCoords) {
        cout << "    ";
        for (int c = 0; c < cols; ++c) cout << setw(3) << (c+1);
        cout << "\n";
    }
    //border linjen
    cout << "    ";
    for (int c = 0; c < cols; ++c) cout << "---";
    cout << "\n";
    //raderna
    for (int r = 0; r < rows; ++r) {
        if (showCoords) cout << setw(3) << (r+1) << " ";
        else cout << " ";

        for (int c = 0; c < cols; ++c) {
            const Cell &cell = grid[r][c];
            char ch='.';
            if (cell.isRevealed()) {
                if (cell.isBomb()) ch='*';
                else if (cell.adjacentBombs()==0) ch=' ';
                else ch = '0'+cell.adjacentBombs();
            } else {
                ch = cell.isFlagged() ? 'F' : '.';
            }

            cout << " " << ch << " ";
        }
        cout << "\n";
    }

    cout << "    ";
    for (int c = 0; c < cols; ++c) cout << "---";
    cout << "\n";
}