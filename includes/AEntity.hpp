#ifndef AENTITY_HPP
# define AENTITY_HPP

#include <iostream>

///////////////
// PROVISOIR //
///////////////
#define X_MIN 0
#define X_MAX 100
#define Y_MIN 0
#define Y_MAX 200

///////////////
typedef enum class	eType
{
	SNAKE, FOOD
}					E_ENTITIES_TYPE;

class AEntity
{
	public :
		AEntity(int x, int y, E_ENTITIES_TYPE type);
		virtual ~AEntity();
		virtual std::pair<int, int>	getPos() const;
		virtual E_ENTITIES_TYPE		getType() const;
		virtual void				setPos(std::pair<int, int> pos);
		virtual void				setType(E_ENTITIES_TYPE type);
		AEntity						(const AEntity &rhs);
		virtual AEntity				&operator=(AEntity const &rhs);

	protected:
		AEntity();
		std::pair<int, int> 		_pos;
		E_ENTITIES_TYPE				_type;
};

#endif
