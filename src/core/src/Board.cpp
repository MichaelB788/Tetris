#include <array>
#include <cstdio>

#include "../include/Board.hpp"

enum Dimensions { ROWS = 21, COLS = 12 };

static unsigned int pointAt(unsigned int x, unsigned int y)
{
    return x + (y * COLS);
}

/* 
 * Grid Dimensions: 21 x 12
 *
 * Character's are used to represents tiles with 
 * special behaviors.
 * */
static std::array<Tile, ROWS * COLS> grid = {
    W, _, _, _, _, _, _, _, _, _, _, W,  
    W, _, _, _, _, _, _, _, _, _, _, W,  
    W, _, _, _, _, _, _, _, _, _, _, W,  
    W, _, _, _, _, _, _, _, _, _, _, W,  
    W, _, _, _, _, _, _, _, _, _, _, W,  
    W, _, _, _, _, _, _, _, _, _, _, W,  
    W, _, _, _, _, _, _, _, _, _, _, W,  
    W, _, _, _, _, _, _, _, _, _, _, W,  
    W, _, _, _, _, _, _, _, _, _, _, W,  
    W, _, _, _, _, _, _, _, _, _, _, W,  
    W, _, _, _, _, _, _, _, _, _, _, W,  
    W, _, _, _, _, _, _, _, _, _, _, W,  
    W, _, _, _, _, _, _, _, _, _, _, W,  
    W, _, _, _, _, _, _, _, _, _, _, W,  
    W, _, _, _, _, _, _, _, _, _, _, W,  
    W, _, _, _, _, _, _, _, _, _, _, W,  
    W, _, _, _, _, _, _, _, _, _, _, W,  
    W, _, _, _, _, _, _, _, _, _, _, W,  
    W, _, _, _, _, _, _, _, _, _, _, W,  
    W, _, _, _, _, _, _, _, _, _, _, W,  
    W, _, _, _, _, _, _, _, _, _, _, W,  
};

Tile Grid::tileAt(unsigned int x, unsigned int y)
{
    return grid[pointAt(x, y)];
}

Tile Grid::tileAt(Point point)
{
    return grid[pointAt(point.getX(), point.getY())];
}

void Grid::set(unsigned int x, unsigned int y, Tile newElement)
{
    grid[pointAt(x, y)] = newElement;
}

void Grid::set(Point point, Tile newElement)
{
    grid[pointAt(point.getX(), point.getY())] = newElement;
}

void Grid::clear(unsigned int row)
{
    while (row > 0)
    {
        for (int col = COLS - 1; col > 0; col--)
            set(col, row, tileAt(col, row - 1));
        row--;
    }
}

void Grid::clear(std::array<Point, 4> target)
{
    for (Point& point : target)
        set( point, _ );
}

bool Grid::hasFullRow(unsigned int row)
{
    // Tiles with values < 7 are playable pieces
    for (int x = 1; x < 12; x++)
        if (tileAt(x, row) < 7 ||
            tileAt(x, row) == _ )
            return false;

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
