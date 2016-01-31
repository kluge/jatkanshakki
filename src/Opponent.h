#ifndef OPPONENT_H
#define OPPONENT_H

#include <Board.h>

typedef double Score;
class QElapsedTimer;

/// Candidate move that has been evaluated to be worth score.
struct Candidate
{
    Point move;
    Score score;
};

class Opponent
{
public:
    constexpr static int timeOut = 1000; ///< maximum time to search for move in milliseconds
    constexpr static Score winScore = 1.0e20; ///< score value for a winning move
    enum Difficulty { Trivial = 0, Easy, Medium, Hard };

    Opponent(Difficulty difficulty);

    Point play(Board const& board);
private:
    Point randomMove(Board const& board);
    std::pair<Candidate, bool> bestMove(Board const& board, int depth, Square player, QElapsedTimer const& timer);
    Score evaluateBoard(Board const& board);

    Difficulty m_difficulty;
};

#endif // OPPONENT_H
