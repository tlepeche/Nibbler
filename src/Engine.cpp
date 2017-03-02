/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Engine.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 22:09:17 by tiboitel          #+#    #+#             */
/*   Updated: 2017/03/02 22:34:52 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Engine.hpp>

Engine::Engine()
{
}

Engine::Engine(Engine const &rhs)
{
	// Copy game pointer here.
}

Engine &Engine::operator=(Engine const &rhs)
{
	if (this != &rhs)
	{
		// Copy game pointer.
	}
	return (*this);
}

Engine::~Engine()
{
	// Delete game
}

Engine::init(void)
{
}

Engine::draw(void)
{
	// Call to graphical wrapper.
}

Engine::handle_game(void)
{
	// Gere la loop principale et les events.
}
