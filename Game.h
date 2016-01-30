#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QStringList>

#include "Board.h"
#include "Opponent.h"

enum class WinCondition
{
    Open = 0,
    XWon = 1,
    OWon = 2
};

class Game : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList board READ board NOTIFY boardChanged)
public:
    explicit Game(QObject* parent = 0);
    QStringList board() const;

signals:
    void boardChanged();
    void gameWon(WinCondition win);

public slots:
    bool playIn(int slot);

private:
    Board m_board;
    Opponent m_opponent;
};

#endif // GAME_H
