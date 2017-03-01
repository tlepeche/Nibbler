#include <Snake.hpp>

Snake::Snake(int x, int y): AEntity(x, y, Snake)
{
	Snake::id += 1;
}

bool	Snake::hasHit(AEntity const & src)
{
	if (_pos.first <= X_MIN || _pos.first >= X_MAX ||
			_pos.second <= Y_MIN || _pos.second >= Y_MAX)
		return true;
	return (_pos == src.getPos());
}

int	Snake::id = 0;
