#include <array>
#include <cstdio>

#include "Grid.hpp"

/* The following functions are used to help navigate the 2D array.
 * These values should not be modified as the grid is immutable.
 * */
enum Dimensions { ROWS = 22, COLS = 12 };

int pointAt(int x, int y){ return x + (y * 12); }

/* 
 * The grid is a immutable single dimension array which represents a
 * 22 x 12 two dimensional array.
 *
 * The behavior of the pieces will rely on checking the neighboring 
 * characters of the array at a given tile.
 *
 * Characters also provide a good way to get a visual representation of 
 * the board, and they will be useful in rendering the board through 
 * Graphics.
 * */
std::array<char, ROWS * COLS> _grid = {
       '|', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '|',
       '|', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '|',
       '|', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '|',
       '|', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '|',
       '|', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '|',
       '|', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '|',
       '|', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '|',
       '|', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '|',
       '|', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '|',
       '|', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '|',
       '|', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '|',
       '|', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '|',
       '|', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '|',
       '|', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '|',
       '|', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '|',
       '|', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '|',
       '|', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '|',
       '|', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '|',
       '|', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '|',
       '|', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '|',
       '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_'
    };

char Grid::at(int x, int y)
{
    return _grid[pointAt(x, y)];
}

char Grid::at(Point point)
{
    return _grid[pointAt(point.getX(), point.getY())];
}

void Grid::set(int x, int y, char newElement)
{
    _grid[pointAt(x, y)] = newElement;
}

void Grid::set(Point point, char newElement)
{
    _grid[pointAt(point.getX(), point.getY())] = newElement;
}

void Grid::clear()
{
    for (auto &element : _grid){
        element = '#';
    }
}

void Grid::printGrid()
{
    for (int row = 0; row < ROWS; row++){
        for (int col = 0; col < COLS; col++){
            printf("%c", Grid::at(col, row));
        }
    printf("\n");
    }
}
