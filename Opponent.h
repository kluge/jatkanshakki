#ifndef OPPONENT_H
#define OPPONENT_H

typedef QStringList Board;
class QStringList;

class Opponent
{
public:
    int play(Board const& board);
};

#endif // OPPONENT_H
