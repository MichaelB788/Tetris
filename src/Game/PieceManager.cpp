#include <stdexcept>

#include "PieceManager.hpp"
#include "Coordinate.hpp"
#include "Board.hpp"

Coordinate::FourPoints PieceManager::giveNewPiece(char type)
{
    switch (type)
    {
        case 'I':
            return Coordinate::FourPoints({{{5, 0}, {5, 1}, {5, 2}, {5, 2}}});
            break;
        case 'O':
            return Coordinate::FourPoints({{{4, 0}, {5, 0}, {4, 1}, {5, 1}}});
            break;
        case 'T':
            return Coordinate::FourPoints({{{3, 0}, {4, 0}, {5, 0}, {4, 1}}});
            break;
        case 'S':
            return Coordinate::FourPoints({{{3, 0}, {4, 0}, {4, 1}, {5, 2}}});
            break;
        case 'Z':
            return Coordinate::FourPoints({{{4, 0}, {5, 0}, {4, 1}, {3, 1}}});
            break;
        case 'L':
            return Coordinate::FourPoints({{{4, 0}, {4, 1}, {4, 2}, {5, 2}}});
            break;
        case 'J':
            return Coordinate::FourPoints({{{5, 0}, {5, 1}, {5, 2}, {4, 2}}});
            break;
        default:
            throw std::invalid_argument("Invalid char type given to PieceManager::giveNewPiece()");
    }
}

bool PieceManager::isValidPosition(Coordinate::FourPoints &coordinates)
{
    for (Coordinate::Point point : coordinates.getFourPoints())
    {
        int x = point.getX();
        int y = point.getY();

        // Coordinate::FourPoints neighbors = Coordinate::getNeighborsAt(point); 

        // TODO: create a function which compares two points
        // I want to see if the neighboring tile is a free tile # 
        if (Board::arrayOfArrays[--x][y] == '#' && Board::arrayOfArrays[++x][y] == '#')
        {
            return true;
        }

        else if (Board::arrayOfArrays[x] == Board::arrayOfArrays[Board::arrayOfArrays.size()])
        { 
            releaseCurrentPiece();
            return false;
        }
    }

    return false;
}

void PieceManager::releaseCurrentPiece()
{
}

