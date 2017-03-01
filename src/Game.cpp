/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 20:07:14 by tiboitel          #+#    #+#             */
/*   Updated: 2017/03/01 20:19:31 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Game.hpp>

Game::Game()
{
}

Game::Game(Game const &rhs)
{
	this->_entities = rhs.getEntities();
}

Game::~Game()
{
}

Game &Game::operator=(Game const &rhs)
{
	if (this != &rhs)
	{
		this->_entities = rhs.getEntities();
	}
	return (*this);
}

std::vector<AEntity *>	Game::getEntities(void) const { return this->_entities; }

int						Game::addEntities(AEntity &entity)
{
	(void)entity;
	return (1);
}

unsigned int			Game::countEntities(void)
{
	return (0);
}

void					Game::update(void)
{
}
