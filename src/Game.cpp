#include <cassert>

#include <QDebug>

#include "Game.h"

/// Check whether either player has won the game.
/// \return symbol of the player that has won or Blank if game has not been won
Square checkWinCondition(Board const& board)
{
    for (auto runLengthsVectors : {rowRunLengths(board),
                                   colRunLengths(board),
                                   downwardDiagonalRunLengths(board),
                                   upwardDiagonalRunLengths(board)}) {
        for (RunLengths const& line : runLengthsVectors) {
            auto iter = std::find_if(line.begin(), line.end(), [](RunLength rl) {
                    return rl.length == Board::TARGET && rl.square != Blank;
            });
            if (iter != line.end()) {
                // found the winner
                return iter->square;
            }
        }
    }
    return Blank;
}

QStringList Game::board() const
{
    QStringList squares;
    for (auto square : m_board) {
        squares << toQString(square);

    }
    return squares;
}

Game::Game(QObject* parent)
    : QObject(parent),
      m_board(),
      m_opponent()
{

}

bool Game::playIn(int slot)
{
    assert(slot >= 0 || size_t(slot) < m_board.size());

    int row = slot / m_board.rows();
    int col = slot % m_board.rows();
    qDebug() << "playIn(" << slot << "): row =" << row << ", col =" << col;

    if (m_board(row, col) != Blank) {
        // slot is already full
        return false;
    }

    m_board(row, col) = X;
    Square winner = checkWinCondition(m_board);

    if (winner == Blank && !m_board.full())
    {
        // still possible for opponent to make a move
        std::pair<int,int> opponentMove = m_opponent.play(m_board);
        qDebug() << "Opponent played" << opponentMove.first << ", " << opponentMove.second;

        m_board(opponentMove.first, opponentMove.second) = O;
        winner = checkWinCondition(m_board);
    }

    emit boardChanged();

    if (winner != Blank || m_board.full()) {
        emit gameOver(winner);
    }

    return true;
}

void Game::newGame(int rows)
{
    qDebug() << "newGame: " << rows;
    m_board = Board(rows);
    emit boardChanged();
}
