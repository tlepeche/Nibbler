/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SpecialFood.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 21:04:15 by tiboitel          #+#    #+#             */
/*   Updated: 2017/03/17 19:21:41 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SpecialFood.hpp>

SpecialFood::SpecialFood(int x, int y, size_t score, size_t lifespan): Food(x, y, score), _lifeSpan(lifespan)
{
	_type = E_ENTITIES_TYPE::SPECIALFOOD;
}

SpecialFood::~SpecialFood()
{
}

SpecialFood::SpecialFood(SpecialFood const & rhs)
{
	*this = rhs;
}

SpecialFood	&SpecialFood::operator=(SpecialFood const & rhs)
{
	if (this != &rhs)
	{
		_pos = rhs.getPos();
		_score = rhs.getScore();
		_type = rhs.getType();
		_lifeSpan = rhs.getLifeSpan();
	}
	return *this;
}

size_t	SpecialFood::getLifeSpan() const { return _lifeSpan; }

void	SpecialFood::setLifeSpan(size_t val)
{
	_lifeSpan -= val > _lifeSpan ? _lifeSpan : val;
}
