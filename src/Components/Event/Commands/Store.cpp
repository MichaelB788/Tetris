#include "Store.hpp"
#include "../../../Game/Objects/Grid.hpp"

void StoreCommand::execute()
{
    p_piece.store();
    Grid::clear(oldPosition);
}
