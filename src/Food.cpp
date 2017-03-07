/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Food.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 21:04:15 by tiboitel          #+#    #+#             */
/*   Updated: 2017/03/07 21:16:16 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Food.hpp>

Food::Food(int x, int y, size_t score) : AEntity(x, y, E_ENTITIES_TYPE::FOOD), _score(score)
{
}

Food::~Food()
{
}

size_t	Food::getScore() const { return _score; }
