#ifndef SNAKE_HPP
# define SNAKE_HPP

#include <AEntity.hpp>

class Snake: public virtual AEntity
{
	public :
		~Snake();
		Snake(int x, int y);
		Snake(Snake const & src);

		bool	hasHit(AEntity const & src);

	private :
		int		_speed;
		int		_velocity;
		Snake();
};

#endif
