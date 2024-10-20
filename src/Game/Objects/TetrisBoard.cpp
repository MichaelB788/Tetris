#include <array>
#include <cstdio>
#include <cstdlib>
#include <ctime>

#include "Coordinate.hpp"
#include "TetrisBoard.hpp"
#include "PieceManager.hpp"

char _types[7] = {'I', 'O', 'T', 'S', 'Z', 'L', 'J'};

std::array<std::array<char, 10>, 20> _grid = {{
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
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'} 
    }};

TetrisBoard::Piece::Piece(char type) :
    coordinates_(PieceManager::giveNewPiece(type)), type_(type)
{
    updatePosition();

    for (auto &i : _grid){
    printf("\n");
        for (auto &j : i)
             printf("%c", j);
    }
};

TetrisBoard::Piece::Piece() 
{
    srand(time(0));
    type_ = _types[rand() % 7];
    coordinates_ = PieceManager::giveNewPiece(type_);
    updatePosition();
};

void TetrisBoard::Piece::updatePosition()
{
    for (Point point : coordinates_)
    {
         Grid::set(point.getX(), point.getY(), type_);
    }
}

void TetrisBoard::Piece::move(Direction dir)
{
    if (PieceManager::positionIsValid(coordinates_))
    {
        switch (dir)
        {
            case LEFT:
                for (Point point : coordinates_){
                    point.translateX(-1);
                }
                break;
            case RIGHT:
                for (Point point : coordinates_){
                    point.translateX(1);
                }
                break;
            case DOWN:
                for (Point point : coordinates_){
                    point.translateY(1);
                }
                break;
            default:
                break;
        }
    }
}

char const TetrisBoard::Grid::at(int x, int y)
{
    return _grid[y][x];
}

char const TetrisBoard::Grid::at(Point c)
{
    return _grid[c.getY()][c.getX()];
}

void TetrisBoard::Grid::set(int x, int y, char newElement)
{
    _grid[y][x] = newElement;
}

void TetrisBoard::Grid::set(Point c, char newElement)
{
    _grid[c.getY()][c.getX()] = newElement;
}
