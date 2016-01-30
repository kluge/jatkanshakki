#include <QDebug>

#include "Game.h"

/// Check whether either player has won the game.
/// \return symbol of the player that has won or Blank if game has not been won
Square checkWinCondition(Board const& board)
{
    int const target = 5; // amount of connected symbols needed to win

    // rows
    for (int r = 0; r != board.rows(); ++r) {
        int count = 0;
        Square current = Blank;
        for (int c = 0; c != board.rows(); ++c) {
            if (board(r, c) != current) {
                count = 1;
                current = board(r, c);
            } else {
                ++count;
                if (count == target && current != Blank) {
                    qDebug() << "Won by " << current;
                    return current;
                }
            }
        }
    }

    // columns
    for (int c = 0; c != board.rows(); ++c) {
        int count = 0;
        Square current = Blank;
        for (int r = 0; r != board.rows(); ++r) {
            if (board(r, c) != current) {
                count = 1;
                current = board(r, c);
            } else {
                ++count;
                if (count == target && current != Blank) {
                    qDebug() << "Won by " << current;
                    return current;
                }
            }
        }
    }

    // downward sloping diagonals below (and including) the main downward diagonal
    for (int rowOffset = 0; rowOffset != board.rows() - target + 1; ++rowOffset) {
        int count = 0;
        Square current = Blank;
        for (int c = 0; c != board.rows() - rowOffset; ++c) {
            Square symbol = board(rowOffset + c, c);
            if (symbol != current) {
                count = 1;
                current = symbol;
            } else {
                ++count;
                if (count == target && current != Blank) {
                    qDebug() << "Won by " << current;
                    return current;
                }
            }
        }
    }

    // downward sloping diagonals above the main diagonal
    for (int colOffset = 1; colOffset != board.rows() - target + 1; ++colOffset) {
        int count = 0;
        Square current = Blank;
        for (int r = 0; r != board.rows() - colOffset; ++r) {
            Square symbol = board(r, colOffset + r);
            if (symbol != current) {
                count = 1;
                current = symbol;
            } else {
                ++count;
                if (count == target && current != Blank) {
                    qDebug() << "Won by " << current;
                    return current;
                }
            }
        }
    }

    // upward sloping diagonals above (and including) the main upward diagonal
    for (int rowOffset = board.rows() - 1; rowOffset != target - 2; --rowOffset) {
        int count = 0;
        Square current = Blank;
        for (int c = 0; c != rowOffset + 1; ++c) {
            Square symbol = board(rowOffset - c, c);
            if (symbol != current) {
                count = 1;
                current = symbol;
            } else {
                ++count;
                if (count == target && current != Blank) {
                    qDebug() << "Won by " << current;
                    return current;
                }
            }
        }
    }

    // upward sloping diagonals below the main upward diagonal
    for (int colOffset = 1; colOffset != board.rows() - target + 1; ++colOffset) {
        int count = 0;
        Square current = Blank;
        for (int r = board.rows() - 1; r != colOffset - 1; --r) {
            Square symbol = board(r, board.rows() - 1 - r + colOffset);
            if (symbol != current) {
                count = 1;
                current = symbol;
            } else {
                ++count;
                if (count == target && current != Blank) {
                    qDebug() << "Won by " << current;
                    return current;
                }
            }
        }
    }

    qDebug() << "No winner yet";
    return Blank;
}

QStringList Game::board() const
{
    QStringList squares;
    for (auto square : m_board) {
        squares << toString(square);

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
    qDebug() << "playIn " << slot;
    if (slot < 0 || size_t(slot) >= m_board.size()) {
        return false;
    }
    int row = slot / m_board.rows();
    int col = slot % m_board.rows();

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
        qDebug() << "Opponent played " << opponentMove.first << ", " << opponentMove.second;
        m_board(opponentMove.first, opponentMove.second) = O;
    }

    emit boardChanged();

    winner = checkWinCondition(m_board);
    if (winner != Blank || m_board.full()) {
        qDebug() << "Emitting gameOver";
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
