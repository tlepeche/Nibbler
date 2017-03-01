#ifndef SNAKE_HPP
# define SNAKE_HPP

#include <AEntity.hpp>

class Snake: public AEntity
{
	Snake();
	~Snake();
	Snake(int x, int y);

	bool	hasHit(AEntity const & src);
};

#endif
