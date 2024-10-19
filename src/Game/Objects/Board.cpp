#include <array>

#include "Coordinate.hpp"
#include "Board.hpp"

std::array<std::array<char, 10>, 20> board = {{
        {'#', '#', '#', '#', 'L', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', 'L', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', 'L', 'L', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'} 
    }};

char Board::at(int row, int col)
{
    return board[row][col];
}

char Board::at(Coordinate::Point c)
{
    return board[c.getX()][c.getY()];
}

void Board::modifyAt(int row, int col, char newElement)
{
    board[row][col] = newElement;
}

void Board::modifyAt(Coordinate::Point c, char newElement)
{
    board[c.getX()][c.getY()] = newElement;
}

void Board::clearRow(int row)
{
    for (char e : board[row]){
        e = '#';
    }
}

void Board::clearBoard()
{
    for (auto &row : board)
        for (auto &col : row)
            col = '#';
}

void Board::shiftRow(int row, int position)
{
}
