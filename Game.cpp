#include <QDebug>
#include <QQmlContext>

#include "Game.h"

QStringList Game::board() const
{
    return m_board;
}

Game::Game(QObject* parent, QQmlContext* context)
    : QObject(parent),
      m_board(),
      m_context(context)
{
    for (int i = 0; i != 5*5; ++i) {
        m_board << " ";
    }
    m_context->setContextProperty("boardModel", QVariant::fromValue(board()));
    m_context->setContextProperty("game", this);
}

bool Game::playIn(int slot)
{
    qDebug() << "playIn " << slot;
    return true;
}
