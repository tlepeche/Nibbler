/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Food.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 21:04:15 by tiboitel          #+#    #+#             */
/*   Updated: 2017/03/17 19:21:07 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Food.hpp>

Food::Food() {}

Food::Food(int x, int y, size_t score): _score(score)
{
   	_pos = std::pair<int, int>(x, y);
	_type = E_ENTITIES_TYPE::FOOD;
}

Food::Food(Food const &rhs)
{
	*this = rhs;
}

Food::~Food()
{
}

size_t	Food::getScore() const { return _score; }

Food	&Food::operator=(Food const &rhs)
{
	if (this != &rhs)
	{
		_pos = rhs.getPos();
		_score = rhs.getScore();
		_type = rhs.getType();
	}
	return *this;
}
