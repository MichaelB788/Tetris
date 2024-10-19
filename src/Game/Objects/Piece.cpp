#include "Piece.hpp"
#include "Coordinate.hpp"
#include "PieceManager.hpp"

Piece::Piece(char type, Board board)
{ 
    coordinates = PieceManager::giveNewPiece(type);
    mBoard = board;

    for (Coordinate::Point point : coordinates.getFourPoints())
    {
        board.modifyAt(point, type);
    }
}

void Piece::move(Direction dir)
{
    if (PieceManager::isValidPosition(coordinates, mBoard))
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
    if (PieceManager::isValidPosition(coordinates, mBoard))
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

