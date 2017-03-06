/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Engine.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 22:09:17 by tiboitel          #+#    #+#             */
/*   Updated: 2017/03/06 19:20:28 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Engine.hpp>

Engine::Engine()
{
}

Engine::Engine(char *DLpath)
{
	try
	{
		this->setRenderer(DLpath);
	} catch (std::exception &e)
	{
		throw(&e);
	}
	this->_game = new Game();
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
	delete _renderer;
	if (dlclose(this->_handler) != 0)
		throw NibblerException("Unable to close handler.");
	delete _game;
}

void	Engine::setRenderer(const char *DLpath)
{
	IRenderer		*(*create_renderer)();

	this->_isPaused = true;
	if (this->_handler != NULL)
	{
		this->_renderer->close();
		if (dlclose(this->_handler) != 0)
			throw EngineDlsymException("Unable to close handler. Error", dlerror(),
					DLpath);
		this->_handler = NULL;
	}
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
	if (!this->_renderer->init(1380/16, 960/16))
		throw NibblerException("Unable to initialize dynamic renderer.");
	this->_isPaused = false;
}

bool	Engine::init(void)
{
	this->_game->init();
	_isPaused = false;
	this->handleGame();
	return (true);
}

void Engine::handleGame(void)
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

		event = _renderer->getLastEvent();
		if (event == E_EVENT_TYPE::QUIT)
		{
			running = false;
			_renderer->close();
			return ;
		}
		if (event == E_EVENT_TYPE::LOAD_LIBRARY_ONE)
			this->setRenderer("sdl/sdl_renderer.so");
		if (event == E_EVENT_TYPE::LOAD_LIBRARY_TWO)
			this->setRenderer("ncurses/ncurse_renderer.so");
		if (this->_isPaused == false && event != E_EVENT_TYPE::RESIZE)
		{
			lag += elapsed / (CLOCKS_PER_SEC / 1000);
			_game->handleInputs(event);
			while (lag >= MS_PER_UPDATE)
			{
				this->_game->update();
				lag -= MS_PER_UPDATE;
			}
			this->_game->draw(this->_renderer);
		}
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
