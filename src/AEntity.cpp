#include <AEntity.hpp>

AEntity::AEntity(int x, int y, E_ENTITIES_TYPE type)
{
	this->setPos(std::pair<int, int>(x, y));
	this->setType(type);
}

AEntity::~AEntity()
{
}

AEntity &AEntity::operator=(AEntity const &rhs)
{
	this->_pos = rhs.getPos();
	this->_type = rhs.getType();
	this->_id = rhs.getID();
	return (*this);
}

std::pair<int, int>	AEntity::getPos() const { return _pos; }
E_ENTITIES_TYPE		AEntity::getType() const { return _type; }
int					AEntity::getID() const { return _id; }

void	AEntity::setType(E_ENTITIES_TYPE type)
{
	this->_type = type;
}

void	AEntity::setPos(std::pair<int, int> pos)
{
	_pos = pos;
}
