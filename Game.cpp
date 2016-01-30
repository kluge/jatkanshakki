#include <QDebug>

#include "Game.h"

WinCondition checkWinCondition(Board const& board)
{
    return WinCondition::Open;
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

    WinCondition win = checkWinCondition(m_board);

    if (win == WinCondition::Open && !m_board.full())
    {
        // still possible for opponent to make a move
        std::pair<int,int> opponentMove = m_opponent.play(m_board);
        m_board(opponentMove.first, opponentMove.second) = O;
    }

    emit boardChanged();

    win = checkWinCondition(m_board);
    if (win != WinCondition::Open) {
        emit gameWon(win);
    }

    return true;
}
