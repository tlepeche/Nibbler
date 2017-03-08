/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Food.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 21:04:15 by tiboitel          #+#    #+#             */
/*   Updated: 2017/03/08 19:26:55 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Food.hpp>

Food::Food() {}

Food::Food(int x, int y, size_t score): _score(score)
{
   	_pos = std::pair<int, int>(x, y);
	_type = E_ENTITIES_TYPE::FOOD;
}

Food::~Food()
{
}

size_t	Food::getScore() const { return _score; }
