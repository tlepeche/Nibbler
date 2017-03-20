#ifndef AENTITY_HPP
# define AENTITY_HPP

#include <iostream>

typedef enum class	eType
{
	SNAKE, FOOD, SPECIALFOOD
}					E_ENTITIES_TYPE;

class AEntity
{
	public :
		AEntity(int x, int y, E_ENTITIES_TYPE type);
		virtual ~AEntity();
		virtual std::pair<int, int>	getPos() const;
		virtual E_ENTITIES_TYPE		getType() const;
		virtual void				setPos(std::pair<int, int> pos);
		virtual void				setPos(int x, int y);
		virtual void				setType(E_ENTITIES_TYPE type);
		AEntity						(const AEntity &rhs);
		virtual AEntity				&operator=(AEntity const &rhs);
	protected:
		AEntity();
		std::pair<int, int> 		_pos;
		E_ENTITIES_TYPE				_type;
};

#endif
