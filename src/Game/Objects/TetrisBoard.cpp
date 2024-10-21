#include <array>
#include <cstdio>
#include <cstdlib>
#include <ctime>

#include "Coordinate.hpp"
#include "TetrisBoard.hpp"
#include "PieceManager.hpp"

char _types[7] = {'I', 'O', 'T', 'S', 'Z', 'L', 'J'};

/* A 10x20 grid is the standard layout for a Tetris board.
 *
 * This 2D array is instantiated with '#' characters, symbolizing free spaces.
 * The character elements will be useful for rendering certain tiles and pieces,
 * and is overall easier to understand than integer types.
 *
 * Accessing and modifying _grid should only be done through namespace Grid.
 * */
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
    newCoordinates_(PieceManager::giveNewPiece(type)), type_(type) {}

TetrisBoard::Piece::Piece() 
{
    srand(time(0));
    type_ = _types[rand() % 7];
    newCoordinates_ = PieceManager::giveNewPiece(type_);
};

void TetrisBoard::Piece::move(Direction dir)
{
    if (PieceManager::positionIsValid(newCoordinates_))
    {
        oldCoordinates_ = newCoordinates_;
        switch (dir)
        {
            case LEFT:
                for (int i = 0; i < 4; i++)
                    newCoordinates_.at(i).translateX(-1);
                break;
            case RIGHT:
                for (int i = 0; i < 4; i++)
                    newCoordinates_.at(i).translateX(1);
                break;
            case DOWN:
                for (int i = 0; i < 4; i++)
                    newCoordinates_.at(i).translateY(1);
                break;
            default:
                break;
        }
    }
}

std::array<Point, 4> TetrisBoard::Piece::getNewCoordinates() const 
{
    std::array<Point, 4> coordinates;

    for (int i = 0; i < 4; i++)
        coordinates[i] = newCoordinates_[i];

    return coordinates;
}

std::array<Point, 4> TetrisBoard::Piece::getOldCoordinates() const 
{
    std::array<Point, 4> coordinates;

    for (int i = 0; i < 4; i++)
        coordinates[i] = oldCoordinates_[i];

    return coordinates;
}

char TetrisBoard::Piece::getType() const
{
    return type_;
}

/* Accessing elements through a 2D array follow the format: array[row][col]
 * This is not to be confused with array[x][y]
 * */
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

void TetrisBoard::Grid::clear()
{
    for (auto &row : _grid){
        for (auto &col : row){
            col = '#';
        }
    }
}
