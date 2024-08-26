# block-game

A simple block game where if a row is filled with blocks, you get points.

This game was made using the SDL2 framework and C++.

## Handling User Input

h - Move Block one tile to the left.
j - Increase fall speed of Block or immediately place it down.
k - Store the block.
l - Move Block one tile to the right.

r - Rotate Block clockwise.

## Game Logic

### Collision Detection

In each frame, a Block object is checked to see if it is within a valid position

A valid position is based on the following criteria:

    - A Block position is only valid if none of its tiles overlap
    with another Block

    - A Block position is invalid if it touches the walls.

    - Once a Block reaches the bottom of the map, stop it's fall speed and give
    the player a new Block

The game board should consist of a 10x20 tiles, with each tile being 20px
in height and length. The board should therefore take up around 200x400 pixels.

Once one row of Block objects is filled, perform the following

    - Clear the row

    - Give the player points (say 100)

## Render Output

I plan to use SDL's built in Rect object.
