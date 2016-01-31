#ifndef OPPONENT_H
#define OPPONENT_H

#include <Board.h>

typedef double Score;

/// Candidate move that has been evaluated to be worth score.
struct Candidate
{
    Point move;
    Score score;
};

class Opponent
{
public:
    enum Difficulty { Trivial = 0, Easy, Medium, Hard };

    Opponent(Difficulty difficulty);

    Point play(Board const& board);
private:
    Point randomMove(Board const& board);
    Candidate bestMove(Board const& board, int depth, Square player);
    Score evaluateBoard(Board const& board);

    Difficulty m_difficulty;

};

#endif // OPPONENT_H
