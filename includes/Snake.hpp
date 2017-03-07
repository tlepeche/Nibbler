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
		void	setVectorX(int x);
		void	setVectorY(int y);
		int		getVectorX();
		int		getVectorY();

	private :
		int		_vector_x;
		int		_vector_y;
		Snake();
};

#endif
