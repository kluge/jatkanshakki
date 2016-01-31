#ifndef OPPONENT_H
#define OPPONENT_H

#include <Board.h>

typedef double Score;

class Opponent
{
public:
    enum Difficulty { Trivial = 0, Easy };

    Opponent(Difficulty difficulty);

    Point play(Board const& board);
private:
    Point randomMove(Board const& board);
    Point bestMove(Board const& board);
    Score evaluateBoard(Board const& board);

    Difficulty m_difficulty;

};

#endif // OPPONENT_H
