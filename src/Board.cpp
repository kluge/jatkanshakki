#include <cassert>

#include "Board.h"

Board::Board(int rows)
    : m_rows(rows),
      m_squares(rows * rows, Blank)
{

}

Square& Board::operator()(int r, int c)
{
    assert(r >= 0 && r < m_rows);
    assert(c >= 0 && c < m_rows);
    return m_squares[m_rows * r + c];
}

Square const& Board::operator()(int r, int c) const
{
    assert(r >= 0 && r < m_rows);
    assert(c >= 0 && c < m_rows);
    return m_squares[m_rows * r + c];
}

int Board::rows() const
{
    return m_rows;
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



std::vector<RunLengths> rowRunLengths(const Board& board)
{
    std::vector<RunLengths> allRows;

    for (int r = 0; r != board.rows(); ++r) {
        RunLengths row;
        int count = 0;
        Square current = Blank;
        for (int c = 0; c != board.rows(); ++c) {
            if (board(r, c) != current) {
                if (count != 0) {
                    row.push_back({current, count});
                }
                count = 1;
                current = board(r, c);
            } else {
                ++count;
            }
        }
        row.push_back({current, count});
        allRows.push_back(row);
    }
    return allRows;
}

std::vector<RunLengths> colRunLengths(const Board& board)
{
    std::vector<RunLengths> allCols;

    for (int c = 0; c != board.rows(); ++c) {
        RunLengths col;
        int count = 0;
        Square current = Blank;
        for (int r = 0; r != board.rows(); ++r) {
            if (board(r, c) != current) {
                if (count != 0) {
                    col.push_back({current, count});
                }
                count = 1;
                current = board(r, c);
            } else {
                ++count;
            }
        }
        col.push_back({current, count});
        allCols.push_back(col);
    }
    return allCols;
}

std::vector<RunLengths> downwardDiagonalRunLengths(const Board& board)
{
    std::vector<RunLengths> allDownwardDiagonals;

    // downward sloping diagonals below (and including) the main downward diagonal
    for (int rowOffset = 0; rowOffset != board.rows() - Board::TARGET + 1; ++rowOffset) {
        RunLengths diagonal;
        int count = 0;
        Square current = Blank;
        for (int c = 0; c != board.rows() - rowOffset; ++c) {
            Square symbol = board(rowOffset + c, c);
            if (symbol != current) {
                if (count != 0) {
                    diagonal.push_back({current, count});
                }
                count = 1;
                current = symbol;
            } else {
                ++count;
            }
        }
        diagonal.push_back({current, count});
        allDownwardDiagonals.push_back(diagonal);
    }

    // downward sloping diagonals above the main diagonal
    for (int colOffset = 1; colOffset != board.rows() - Board::TARGET + 1; ++colOffset) {
        RunLengths diagonal;
        int count = 0;
        Square current = Blank;
        for (int r = 0; r != board.rows() - colOffset; ++r) {
            Square symbol = board(r, colOffset + r);
            if (symbol != current) {
                if (count != 0) {
                    diagonal.push_back({current, count});
                }
                count = 1;
                current = symbol;
            } else {
                ++count;
            }
        }
        diagonal.push_back({current, count});
        allDownwardDiagonals.push_back(diagonal);
    }

    return allDownwardDiagonals;
}

std::vector<RunLengths> upwardDiagonalRunLengths(const Board& board)
{
    std::vector<RunLengths> allUpwardDiagonals;

    // upward sloping diagonals above (and including) the main upward diagonal
    for (int rowOffset = board.rows() - 1; rowOffset != Board::TARGET - 2; --rowOffset) {
        RunLengths diagonal;
        int count = 0;
        Square current = Blank;
        for (int c = 0; c != rowOffset + 1; ++c) {
            Square symbol = board(rowOffset - c, c);
            if (symbol != current) {
                if (count != 0) {
                    diagonal.push_back({current, count});
                }
                count = 1;
                current = symbol;
            } else {
                ++count;
            }
        }
        diagonal.push_back({current, count});
        allUpwardDiagonals.push_back(diagonal);
    }

    // upward sloping diagonals below the main upward diagonal
    for (int colOffset = 1; colOffset != board.rows() - Board::TARGET + 1; ++colOffset) {
        RunLengths diagonal;
        int count = 0;
        Square current = Blank;
        for (int r = board.rows() - 1; r != colOffset - 1; --r) {
            Square symbol = board(r, board.rows() - 1 - r + colOffset);
            if (symbol != current) {
                if (count != 0) {
                    diagonal.push_back({current, count});
                }
                count = 1;
                current = symbol;
            } else {
                ++count;
            }
        }
        diagonal.push_back({current, count});
        allUpwardDiagonals.push_back(diagonal);
    }

    return allUpwardDiagonals;
}
