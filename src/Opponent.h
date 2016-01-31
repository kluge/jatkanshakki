#ifndef OPPONENT_H
#define OPPONENT_H

class Board;
typedef double Score;

class Opponent
{
public:
    enum Difficulty { Trivial = 0, Easy };

    Opponent(Difficulty difficulty);

    std::pair<int,int> play(Board const& board);
private:
    std::pair<int,int> randomMove(Board const& board);
    std::pair<int,int> bestMove(const Board& board);
    Score evaluateBoard(Board const& board);

    Difficulty m_difficulty;

};

#endif // OPPONENT_H
