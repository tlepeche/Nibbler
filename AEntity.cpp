#include <AEntity.hpp>

AEntity::AEntity(): _type(Snake) {}

AEntity::~AEntity() {}

AEntity::AEntity(int x, int y, eType type): _type(type)
{
	_pos.first = x;
	_pos.second = y;
}

AEntity::AEntity(AEntity const & src): _type(src.getType())
{
	*this = src;
}

AEntity &AEntity::operator=(AEntity const & src)
{
	_pos = src.getPos();
	return *this;
}

std::pair<int, int>	AEntity::getPos() const { return _pos; }

eType				AEntity::getType() const { return _type; }

void	AEntity::setPos(std::pair<int, int> pos)
{
	_pos = pos;
}
