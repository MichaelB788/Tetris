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

static unsigned int pointAt(unsigned int x, unsigned int y)
{
    return x + (y * COLS);
}

static bool isFloor(char tile)
{
    return 'i' <= tile && tile <= 'z';
}

/* 
 * Grid Dimensions: 20 x 12
 *
 * Character's are used to represents tiles with 
 * special behaviors.
 * */
static std::array<char, ROWS * COLS> grid = {
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
       '|', 'o', '#', '#', '#', '#', '#', '#', '#', '#', '#', '|',
       '|', 'o', 'o', '#', '#', '#', '#', '#', '#', '#', '#', '|',
       '|', 'o', 'o', '#', '#', '#', '#', '#', '#', '#', '#', '|',
       '|', 'o', 'o', 'o', 'o', '#', '#', 'o', 'o', 'o', 'o', '|',
    };

char Grid::tileAt(unsigned int x, unsigned int y)
{
    return grid[pointAt(x, y)];
}

char Grid::tileAt(Point point)
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

void Grid::clear(unsigned int row)
{
    if (row > 19) row = 19;
    
    while (row > 0)
    {
        for (int col = COLS - 1; col > 0; col--)
        {
            // if (row == 0) set(col, row, '#');
            set(col, row, tileAt(col, row - 1));
        }
        row--;
    }
}

// Check each row and see if it does not contain '#'
bool Grid::hasFullRow(unsigned int row)
{
    if (row > 19) row = 19;
    unsigned int x = 1;

    while (tileAt(x, row) != '|')
    {
        if (tileAt(x, row) == '#' || !isFloor(tileAt(x, row)))
            return false;
        else x++;
    }

    return true;
}

// FOR TESTING ONLY
void Grid::printGrid()
{
    for (int row = 0; row < ROWS; row++)
    {
        for (int col = 0; col < COLS; col++)
        {
            printf("%c", Grid::tileAt(col, row));
        }
    printf("\n");
    }
}
