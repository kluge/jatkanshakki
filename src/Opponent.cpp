#include "Board.h"

#include "Opponent.h"

std::pair<int, int> Opponent::play(const Board& board)
{
    int row;
    int col;

    do {
        row = qrand() % board.rows();
        col = qrand() % board.rows();
    } while (board(row, col) != Blank);

    return std::make_pair(row, col);
}
