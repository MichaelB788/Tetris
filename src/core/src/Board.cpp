#include <array>
#include <cstdio>

#include "Board.hpp"

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
