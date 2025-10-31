#include "core/command.hpp"

void MoveDownCommand::execute() {
	m_actor.shift(Vector2::down);
	if (!m_scene.place(m_actor)) {
		m_actor.shift(Vector2::up);
	}
}
