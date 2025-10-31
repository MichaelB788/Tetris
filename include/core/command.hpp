#ifndef COMMAND_H
#define COMMAND_H
#include "core/matrix.hpp"
#include "core/tetromino.hpp"
#include "util/vector2.hpp"

class Command {
public:
	Command(Matrix& matrix, Tetromino& tetromino)
		: m_scene(matrix),
			m_actor(tetromino)
	{}; 
	virtual ~Command();
	virtual void execute() = 0;

protected:
	Matrix& m_scene;
	Tetromino& m_actor;
};

class MoveDownCommand : public Command {
public:
	MoveDownCommand(Matrix& matrix, Tetromino& tetromino)
		: Command(matrix, tetromino)
	{}; 
	void execute() override;
};

#endif
