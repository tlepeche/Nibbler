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
enum	eType {Snake, Food};

class AEntity
{
	public :
		AEntity(int x, int y, eType type);
		~AEntity();
		AEntity(AEntity const & src);
		AEntity & operator=(AEntity const & src);
		
		std::pair<int, int>	getPos() const;
		eType				getType() const;
		void				setPos(std::pair<int, int> pos);

	private :
		AEntity();
		std::pair<int, int> _pos;
		const eType			_type;
};

#endif
