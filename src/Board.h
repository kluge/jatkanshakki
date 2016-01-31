#ifndef BOARD_H
#define BOARD_H

#include <vector>

#include <QString>

/// The different states a tic tac toe square can be in.
enum Square {
    Blank = 0,
    X,
    O
};

/// Convert Square to the traditional ASCII representation.
inline
QString toString(Square square) {
    switch (square) {
    case X:
        return "X";
    case O:
        return "O";
    default:
        return " ";
    }
}

/// A variable-sized square board for tic tac toe.
class Board
{
public:
    Board(int rows = 5);

    Square& operator()(int r, int c);
    Square const& operator()(int r, int c) const;

    /// Amount of rows (and columns) in the square grid
    int rows() const;

    typedef std::vector<Square>::const_iterator const_iterator;
    typedef std::vector<Square>::iterator iterator;

    const_iterator begin() const;
    iterator begin();

    const_iterator end() const;
    iterator end();

    /// Total amount of squares on the board.
    size_t size() const;

    /// Whether all the squares on the board are already full.
    bool full() const;
private:
    int m_rows;
    std::vector<Square> m_squares;
};

#endif // BOARD_H
