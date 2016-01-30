#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QStringList>

class Game : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList board READ board NOTIFY boardChanged)
public:
    explicit Game(QObject* parent = 0);
    QStringList board() const;

signals:
    void boardChanged();

public slots:
    bool playIn(int slot);

private:
    QStringList m_board;
};

#endif // GAME_H
