#ifndef OPPONENT_H
#define OPPONENT_H

#include "Board.h"

class Opponent
{
public:
    std::pair<int,int> play(Board const& board);
};

#endif // OPPONENT_H
