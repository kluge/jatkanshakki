#ifndef BOARD_H
#define BOARD_H

#include <vector>

#include <QString>

enum Square {
    Blank = 0,
    X,
    O
};

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

class Board
{
public:
    Board(int rows = 5, int cols = 5);

    Square& operator()(int r, int c);
    Square const& operator()(int r, int c) const;

    int rows() const;
    int cols() const;

    typedef std::vector<Square>::const_iterator const_iterator;
    typedef std::vector<Square>::iterator iterator;

    const_iterator begin() const;
    iterator begin();

    const_iterator end() const;
    iterator end();

    size_t size() const;

    bool full() const;
private:
    int m_rows;
    int m_cols;
    std::vector<Square> m_squares;
};

#endif // BOARD_H
