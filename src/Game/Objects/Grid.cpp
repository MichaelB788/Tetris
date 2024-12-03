#include <array>
#include <cstdio>

#include "Grid.hpp"

/* The following functions are used to help navigate
 * the "2D array."
 *
 * These values should not be modified and may only be
 * used in this file.
 * */
enum Dimensions { ROWS = 20, COLS = 12 };

int pointAt(int x, int y){ return x + (y * COLS); }

/* 
 * Grid Dimensions: 20 x 12
 *
 * Character's are used to represents tiles with 
 * special behaviors.
 * */
std::array<char, ROWS * COLS> grid = {
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
    };

char Grid::at(unsigned int x, unsigned int y)
{
    return grid[pointAt(x, y)];
}

char Grid::at(Point point)
{
    return grid[pointAt(point.getX(), point.getY())];
}

void Grid::set(unsigned int x, unsigned int y, char newElement)
{
    grid[pointAt(x, y)] = newElement;
}

void Grid::set(Point point, char newElement)
{
    grid[pointAt(point.getX(), point.getY())] = newElement;
}

void Grid::clear()
{
    for (auto &element : grid) element = '#';
}

void Grid::clear(unsigned int row)
{
    for (int col = 0; col < 10; col++)
    {
        set(col + 1, row - 1, '#');
    }
}

// FOR TESTING ONLY
void Grid::printGrid()
{
    for (int row = 0; row < ROWS; row++)
    {
        for (int col = 0; col < COLS; col++)
        {
            printf("%c", Grid::at(col, row));
        }
    printf("\n");
    }
}
