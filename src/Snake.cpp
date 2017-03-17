#include <Snake.hpp>

Snake::Snake(int x, int y) : AEntity(x, y, E_ENTITIES_TYPE::SNAKE), _vector_x(0), _vector_y(0)
{}

Snake::Snake(Snake const & src)
{
	*this = src;
}

Snake	&Snake::operator=(const Snake &src)
{
	if (this != &src)
	{
		_pos = src.getPos();
		_type = src.getType();
		_vector_x = src.getVectorX();
		_vector_y = src.getVectorY();
	}
	return *this;
}

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

int		Snake::getVectorX() const { return _vector_x; }

int		Snake::getVectorY() const { return _vector_y; }

bool	Snake::hasHit(AEntity const & src)
{
	if (this == &src)
		return false;
	if (getPos().first <= X_MIN || getPos().first >= X_MAX ||
			getPos().second <= Y_MIN || getPos().second >= Y_MAX)
		return true;
	return (getPos() == src.getPos());
}
