#include <QStringList>

#include "Opponent.h"

int Opponent::play(const Board& board)
{
    int choice;
    do {
        choice = qrand() % board.size();
    } while (board[choice] != " ");
    return choice;
}
