#ifndef TYPE_H
#define TYPE_H

typedef enum Tile
{
    // Playable piece types [0 - 6]
    I, O, T, Z, S, J, L,

    // Unplayable piece types [7 - 13]
    // Note: to ground a piece, add it by 7
    i, o, t, z, s, j, l,
    
    // Wall and free spaces 
    // Note: Starts at 99 to avoid grounding an
    // already grounded piece
    W = 99, _, NIL 
} Tile;

#endif 
