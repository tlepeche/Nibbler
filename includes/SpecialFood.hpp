#ifndef SPECIALFOOD_HPP
# define SPECIALFOOD_HPP

# include <Food.hpp>

class SpecialFood : public Food
{
	public:
		SpecialFood(int x, int y, size_t score = 200, size_t lifespan = 10000);
		~SpecialFood();
		SpecialFood		(SpecialFood const &rhs);
		SpecialFood		&operator=(SpecialFood const &rhs);
		size_t			getLifeSpan() const;
		void			setLifeSpan(size_t val);

	private:
		SpecialFood();
		size_t		_lifeSpan; //lifespan in ms
};

#endif
