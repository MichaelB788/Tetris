#include "Piece.hpp"
#include "Coordinate.hpp"
#include "PieceManager.hpp"

typedef enum Piece::Direction : unsigned int 
{
    LEFT, RIGHT, DOWN
} Direction;

Piece::Piece(char type)
{ 
    coordinates = PieceManager::giveNewPiece(type);

    for (Coordinate::Point point : coordinates.getFourPoints())
    {
         Board::arrayOfArrays[point.getX()][point.getY()] = type; 
    }
}

void Piece::move(Direction dir)
{
    if (PieceManager::isValidPosition(coordinates))
    {
        switch (dir)
        {
            case LEFT:
                for (Coordinate::Point point : coordinates.getFourPoints()){
                    point.translateX(-1);
                }
                break;
            case RIGHT:
                for (Coordinate::Point point : coordinates.getFourPoints()){
                    point.translateX(1);
                }
                break;
            case DOWN:
                for (Coordinate::Point point : coordinates.getFourPoints()){
                    point.translateY(1);
                }
                break;
            default:
                break;
        }
    }
}

void Piece::rotate(Direction dir)
{
    if (PieceManager::isValidPosition(coordinates))
    {
        switch (dir) {
            case LEFT:
                break;
            case RIGHT:
                break;
            default:
                break;
        }
    }
}
