#include "Board.h"

Board::Board(int rows, int cols)
    : m_rows(rows),
      m_cols(cols),
      m_squares(rows * cols, Blank)
{

}

Square& Board::operator()(int r, int c)
{
    return m_squares[m_rows * r + c];
}

Square const& Board::operator()(int r, int c) const
{
    return m_squares[m_rows * r + c];
}

int Board::rows() const
{
    return m_rows;
}

int Board::cols() const
{
    return m_cols;
}

Board::const_iterator Board::begin() const
{
    return m_squares.begin();
}

Board::iterator Board::begin()
{
    return m_squares.begin();
}

Board::const_iterator Board::end() const
{
    return m_squares.end();
}

Board::iterator Board::end()
{
    return m_squares.end();
}

size_t Board::size() const
{
    return m_squares.size();
}

bool Board::full() const
{
    return std::find(m_squares.begin(), m_squares.end(), Blank) == m_squares.end();
}
