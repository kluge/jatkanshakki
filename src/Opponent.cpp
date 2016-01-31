#include "Board.h"

#include "Opponent.h"

Opponent::Opponent(Opponent::Difficulty difficulty)
    : m_difficulty(difficulty)
{

}


Point Opponent::play(const Board& board)
{
    if (m_difficulty == Trivial) {
        return randomMove(board);
    } else {
        return bestMove(board);
    }
}

/// Returns a random valid move for O
Point Opponent::randomMove(const Board& board)
{
    int row;
    int col;

    do {
        row = qrand() % board.rows();
        col = qrand() % board.rows();
    } while (board(row, col) != Blank);

    return Point{row, col};
}

/// Return Manhattan distance from point (\a r, \a c) to the center of the board with \a rows rows.
int distanceToCenter(Point point, int rows) {
    // for even number of rows we'll favor lower right corner, but that's OK
    int midR = rows / 2 + 1;
    int midC = rows / 2 + 1;
    return std::abs(midR - point.row) + std::abs(midC + point.column);
}

/// Returns the best available move for O according to evaluateBoard()
Point Opponent::bestMove(const Board& board)
{
    // try every move and use the best one
    Point candidate;
    Score score = -std::numeric_limits<Score>::max();

    for (int r = 0; r != board.rows(); ++r) {
        for (int c = 0; c != board.rows(); ++c) {
            if (board(r, c) == Blank) {
                Board future{board};
                future(r, c) = O;
                int futureScore = evaluateBoard(future);
                if (futureScore > score) {
                    candidate = Point{r, c};
                    score = futureScore;
                } else if (futureScore == score) {
                    // prefer central squares when scores are equal
                    if (distanceToCenter(candidate, board.rows()) > distanceToCenter(Point{r, c}, board.rows())) {
                        candidate = Point{r, c};
                        score = futureScore;
                    }
                }
            }
        }
    }
    return candidate;
}

/// Representation of a possibility on a line
struct Possibility {
    Square player; ///< which player has the possibility
    int current; ///< how many marks player already has in the possibility
    int capacity; ///< how many marks player can place in the possibility
    bool doubleEnded; ///< whether both ends of the possibility are open
};

/// Return the amount of blank squares on the line next to index and whether
/// there are blank squares on both sides.
std::pair<int, bool> evaluateBlankNeighbors(size_t index, RunLengths const& line)
{
    int blankNeighbors = 0;
    bool bothNeighborsBlank = true;

    // check before
    if (int(index) - 1 >= 0 && line[index - 1].square == Blank) {
        blankNeighbors += line[index - 1].length;
    } else {
        bothNeighborsBlank = false;
    }

    // check after
    if (index + 1 < line.size() && line[index + 1].square == Blank) {
        blankNeighbors += line[index + 1].length;
    } else {
        bothNeighborsBlank = false;
    }

    return std::make_pair(blankNeighbors, bothNeighborsBlank);
}

/// Return the value of a possibility from O's perspective.
Score evaluatePossibility(Possibility possibility) {
    Score sign = possibility.player == O ? 1 : -1;
    if (possibility.capacity < Board::TARGET) {
        // non-winning possibilities count for nothing
        return 0.0;
    }
    if (possibility.current == Board::TARGET)
    {
        // obviously winning is important
        return sign * std::pow(10, 10);
    }
    return sign * std::pow(10, possibility.current + (possibility.doubleEnded ? 0.5 : 0));
}

/// Calculate the value of the board from O's perspective.
Score Opponent::evaluateBoard(const Board& board)
{
    std::vector<Possibility> possibilities;

    // determine the possibilities each player has
    for (auto runLengthsVectors : {rowRunLengths(board),
                                   colRunLengths(board),
                                   downwardDiagonalRunLengths(board),
                                   upwardDiagonalRunLengths(board)}) {
        for (RunLengths const& line : runLengthsVectors) {
            for (size_t i = 0; i != line.size(); ++i) {
                if (line[i].square != Blank) {
                    // possibility for one player
                    Possibility possibility;
                    possibility.player = line[i].square;
                    possibility.current = line[i].length;
                    std::pair<int, bool> blankResults = evaluateBlankNeighbors(i, line);
                    possibility.capacity = possibility.current + blankResults.first;
                    possibility.doubleEnded = blankResults.second;

                    possibilities.push_back(possibility);
                }
            }
        }
    }

    // calculate the value of possibilities
    Score score = 0;
    for (auto possibility : possibilities) {
        score += evaluatePossibility(possibility);
    }
    return score;
}
