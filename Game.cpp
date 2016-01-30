#include <QDebug>

#include "Game.h"

QStringList Game::board() const
{
    return m_board;
}

Game::Game(QObject* parent)
    : QObject(parent),
      m_board()
{
    for (int i = 0; i != 5*5; ++i) {
        m_board << " ";
    }
}

bool Game::playIn(int slot)
{
    qDebug() << "playIn " << slot;
    if (slot < 0 || slot >= m_board.size()) {
        return false;
    }
    m_board[slot] = "X";
    emit boardChanged();
    return true;
}
