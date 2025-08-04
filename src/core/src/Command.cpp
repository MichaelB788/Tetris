#include "../include/Command.hpp"
#include "../include/Mechanics.hpp"
#include "../include/Board.hpp"
#include <array>

void MoveCommand::execute(Tetromino& TetrominoActor)
{
    TetrominoActor.translate(DOWN);

    if (Mechanics::collidesObject(p_piece))
        enforceCollision();

    else Grid::clear(oldPosition);
}
