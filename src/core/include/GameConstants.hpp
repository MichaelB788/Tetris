#pragma once

enum Direction { LEFT, RIGHT, DOWN };

enum Difficulty { EASY = 200, NORMAL = 100, HARD = 50 }; 
enum GameState { RUNNING, GAME_OVER, PAUSED, EXIT };

enum BoardDimension { WIDTH = 10, HEIGHT = 20 };

enum PieceType { I, O, T, Z, S, J, L, NONE };
enum TileState { FALLING, GROUNDED, EMPTY };
struct Tile
{
	PieceType m_Type;
	TileState m_State;

	Tile() : m_Type(NONE), m_State(EMPTY) {};
};
