/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Engine.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 22:09:17 by tiboitel          #+#    #+#             */
/*   Updated: 2017/03/20 15:30:38 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Engine.hpp>
#include <unistd.h>

Engine::Engine()
{
}

Engine::Engine(char *width, char *height): _hasLost(false), _handler(NULL)
{
	_game = new Game(width, height);
	setRenderer("sfml/sfml_renderer.so");
}

Engine::Engine(Engine const &rhs)
{
	*this = rhs;
}

Engine &Engine::operator=(Engine const &rhs)
{
	if (this != &rhs)
	{
		_isPaused = rhs.getIsPaused();
		_hasLost = rhs.getHasLost();
		_game = rhs.getGame();
		_renderer = rhs.getRenderer();
		_handler = rhs.getHandler();
	}
	return (*this);
}

bool		Engine::getIsPaused() const { return _isPaused; }
bool		Engine::getHasLost() const { return _hasLost; }
Game		*Engine::getGame() const { return _game; }
IRenderer	*Engine::getRenderer() const { return _renderer; }
void		*Engine::getHandler() const { return _handler; }

Engine::~Engine()
{
	delete _renderer;
	if (dlclose(_handler) != 0)
		throw NibblerException("Unable to close handler.");
	delete _game;
}

void	Engine::setRenderer(const char *DLpath)
{
	IRenderer		*(*create_renderer)();

	_isPaused = true;
	if (_handler != NULL)
	{
		_renderer->close();
		if (dlclose(_handler) != 0)
			throw EngineDlsymException("Unable to close handler. Error", dlerror(), DLpath);
		_handler = NULL;
	}
	_handler = dlopen(DLpath, RTLD_LAZY);
	if (!_handler)
		throw EngineDlsymException("Unable to dlopen. Error", dlerror(), DLpath);
	create_renderer = reinterpret_cast<IRenderer * (*)()>(dlsym(_handler, "create_renderer"));
	if (!create_renderer)
		throw EngineDlsymException("Unable to find symbol. Error", dlerror(), DLpath);
	_renderer = create_renderer();
	if (!_renderer->init(_game->getWidth(), _game->getHeight()))
		throw NibblerException("Unable to initialize dynamic renderer.");
	_isPaused = false;
}

bool	Engine::init(void)
{
	_game->init();
	_isPaused = false;
	handleGame();
	return (true);
}

void Engine::handleGame(void)
{
	E_EVENT_TYPE		event;
	bool				running = true;
	double				frameRate = 30;
	std::clock_t		deltaTime;
	std::clock_t		endFrame;

	//DEBUG
	//	clock_t VERIF = 0;
	//	int		frames = 0;

	//VITESSE AVEC FPS
	//	bool				change = true;

	while (running)
	{
		if (std::rand() % 100 == 1 && !(_game->getSpeFood()) && !_hasLost)
			_game->addSpecialFood();
		//		std::clock_t TEST = std::clock();
		std::clock_t startFrame = std::clock();
		event = _renderer->getLastEvent();
		if (event == E_EVENT_TYPE::QUIT)
		{
			running = false;
			_renderer->close();
			return ;
		}
		else if (event == E_EVENT_TYPE::LOAD_LIBRARY_ONE)
		{
			try
			{
				setRenderer("sdl/sdl_renderer.so");
			}
			catch (std::exception &e)
			{
				std::cout << e.what() << std::endl;
				exit(0);
			}
		}
		else if (event == E_EVENT_TYPE::LOAD_LIBRARY_TWO)
		{
			try
			{
				setRenderer("ncurses/ncurse_renderer.so");
			}
			catch (std::exception &e)
			{
				std::cout << e.what() << std::endl;
				exit(0);
			}
		}
		else if (event == E_EVENT_TYPE::LOAD_LIBRARY_THREE)
		{
			try
			{
				setRenderer("SFML/sfml_renderer.so");
			}
			catch (std::exception &e)
			{
				std::cout << e.what() << std::endl;
				exit(0);
			}
		}
		endFrame = std::clock();
		if (_isPaused == false && event != E_EVENT_TYPE::RESIZE)
		{
			if (!_hasLost)
			{
				_game->handleInputs(event);
				_game->changePos();
				if (!(_game->update()))
					_hasLost = true;
			}
			_game->draw(_renderer, _hasLost);
		}
		deltaTime = endFrame - startFrame;
		while (((deltaTime / (double)CLOCKS_PER_SEC) * 1000.0) < (1000.0 / frameRate))
		{
			endFrame = std::clock();
			deltaTime = endFrame - startFrame;
			_game->handleInputs(event);
		}

		// PERMET D'AUGMENTER LES FPS EN FONCTION DU SCORE
		/*		if (_game->getScore() % 400 == 0 && _game->getScore() != 0 && change == true)
				{
				change = false;
				frameRate *= 2;
				}
				else if (_game->getScore() % 400 != 0)
				change = true;*/


		//		DEBUG
		/*		frames++;
				VERIF += endFrame- TEST;
				std::cout << frames << std::endl;
				std::cout << ((VERIF / (double)CLOCKS_PER_SEC) * 1000.0) << std::endl;
				if (((VERIF)/CLOCKS_PER_SEC*1000.0) > 1000.0)
				{
				frames = 0;
				VERIF -= CLOCKS_PER_SEC;
				}*/
		if (_game->getSpeFood() && !_hasLost)
		{
			SpecialFood	*speFood = _game->getSpeFood();
			speFood->setLifeSpan(deltaTime);
			if (speFood->getLifeSpan() == 0)
				_game->eraseEntity(speFood);
		}
		deltaTime = 0;
	}
}

EngineDlsymException::EngineDlsymException(const char *msg, const char *dlerror, const char *library_path) : NibblerException(msg)
{
	std::stringstream	ss;

	ss << msg << ": " << dlerror << " on dylib includes : " << library_path;
	_error = ss.str();
}

const char *EngineDlsymException::what(void) const throw()
{
	return (_error.c_str());
}
