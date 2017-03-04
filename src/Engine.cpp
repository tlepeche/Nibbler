/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Engine.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 22:09:17 by tiboitel          #+#    #+#             */
/*   Updated: 2017/03/04 19:25:44 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Engine.hpp>

Engine::Engine()
{
}

Engine::Engine(char *DLpath)
{
	IRenderer		*(*create_renderer)();

	this->_handler = dlopen(DLpath, RTLD_LAZY);
	if (!this->_handler)
		throw EngineDlsymException("Unable to dlopen. Error", dlerror(),
				DLpath);
	create_renderer = reinterpret_cast<IRenderer * (*)()>(
			dlsym(this->_handler, "create_renderer"));
	if (!create_renderer)
		throw EngineDlsymException("Unable to find symbol. Error", dlerror(),
				DLpath);
	this->_renderer = create_renderer();
	this->_game = new Game();
	this->_game->init();
	this->_renderer->init(1380, 960);
}

Engine::Engine(Engine const &rhs)
{
	(void)rhs;
	// Copy game pointer here.
}

Engine &Engine::operator=(Engine const &rhs)
{
	if (this != &rhs)
	{
		(void)rhs;
		// Copy game pointer.
	}
	return (*this);
}

Engine::~Engine()
{
	if (dlclose(this->_handler) != 0)
		throw NibblerException("Unable to close dynamic library");
	delete _game;
}

bool Engine::init(void)
{
	handle_game();
	return (true);
}

void Engine::handle_game(void)
{
	std::clock_t 		previous = std::clock();
	double 				lag = 0;
	E_EVENT_TYPE		event;
	bool				running;

	running = true;
	while (running)
	{
		std::clock_t	current =  std::clock();
		double		 	elapsed = current - previous;
		lag += elapsed / (CLOCKS_PER_SEC / 1000);
		event = _renderer->getLastEvent();
		if (event == E_EVENT_TYPE::QUIT)
		{
			running = false;
			_renderer->close();
		}
		/*
		 ** Si l'event est d'un type different le transmettre a game.
		 */
		while (lag >= MS_PER_UPDATE)
		{
			this->_game->update();
			lag -= MS_PER_UPDATE;
		}
		this->_game->draw(this->_renderer);
	}
}

EngineDlsymException::EngineDlsymException(const char *msg, const char *dlerror, const char *library_path) : NibblerException(msg)
{
	std::stringstream	ss;

	ss << msg << ": " << dlerror << " on dylib includes : " << library_path;
	this->_error = ss.str();
}

const char *EngineDlsymException::what(void) const throw()
{
	return (this->_error.c_str());
}
