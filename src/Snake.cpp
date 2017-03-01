#include <Snake.hpp>

Snake::Snake(int x, int y) : AEntity(x, y, E_ENTITIES_TYPE::SNAKE)
{
}

Snake::~Snake()
{
}

bool	Snake::hasHit(AEntity const & src)
{
	if (getPos().first <= X_MIN || getPos().first >= X_MAX ||
			getPos().second <= Y_MIN || getPos().second >= Y_MAX)
		return true;
	return (getPos() == src.getPos());
}
