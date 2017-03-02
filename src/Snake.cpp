#include <Snake.hpp>

Snake::Snake(int x, int y) : AEntity(x, y, E_ENTITIES_TYPE::SNAKE)
{}

Snake::Snake(Snake const & src): Snake(src.getPos().first, src.getPos().second)
{}

Snake::~Snake()
{}

bool	Snake::hasHit(AEntity const & src)
{
	if (this == &src)
		return false;
	if (getPos().first <= X_MIN || getPos().first >= X_MAX ||
			getPos().second <= Y_MIN || getPos().second >= Y_MAX)
		return true;
	return (getPos() == src.getPos());
}
