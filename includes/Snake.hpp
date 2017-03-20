#ifndef SNAKE_HPP
# define SNAKE_HPP

#include <AEntity.hpp>

class Snake: public virtual AEntity
{
	public :
		~Snake();
		Snake(int x, int y);
		Snake(Snake const & src);
		Snake	&operator=(const Snake &src);

		void	setVectorX(int x);
		void	setVectorY(int y);
		int		getVectorX() const;
		int		getVectorY() const;

	private :
		int		_vector_x;
		int		_vector_y;
		Snake();
};

#endif
