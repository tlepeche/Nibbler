#include <Snake.hpp>

Snake::Snake(int x, int y) : AEntity(x, y, E_ENTITIES_TYPE::SNAKE)
{}

Snake::Snake(Snake const & src): Snake(src.getPos().first, src.getPos().second)
{}

Snake::~Snake()
{}

void	Snake::setVectorX(int x)
{
	_vector_x = x;
}

void	Snake::setVectorY(int y)
{
	_vector_y = y;
}

int		Snake::getVectorX() { return _vector_x; }

int		Snake::getVectorY() { return _vector_y; }

bool	Snake::hasHit(AEntity const & src)
{
	if (this == &src)
		return false;
	if (getPos().first <= X_MIN || getPos().first >= X_MAX ||
			getPos().second <= Y_MIN || getPos().second >= Y_MAX)
		return true;
	return (getPos() == src.getPos());
}
