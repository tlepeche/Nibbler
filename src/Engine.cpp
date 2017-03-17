/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Engine.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 22:09:17 by tiboitel          #+#    #+#             */
/*   Updated: 2017/03/17 16:26:53 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Engine.hpp>
#include <unistd.h>

Engine::Engine()
{
}

Engine::Engine(char *DLpath): _hasLost(false), _handler(NULL)
{
	this->setRenderer(DLpath);
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
			throw EngineDlsymException("Unable to close handler. Error", dlerror(), DLpath);
		this->_handler = NULL;
	}
	this->_handler = dlopen(DLpath, RTLD_LAZY);
	if (!this->_handler)
		throw EngineDlsymException("Unable to dlopen. Error", dlerror(), DLpath);
	create_renderer = reinterpret_cast<IRenderer * (*)()>(dlsym(this->_handler, "create_renderer"));
	if (!create_renderer)
		throw EngineDlsymException("Unable to find symbol. Error", dlerror(), DLpath);
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
				this->setRenderer("sdl/sdl_renderer.so");
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
				this->setRenderer("ncurses/ncurse_renderer.so");
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
				this->setRenderer("SFML/sfml_renderer.so");
			}
			catch (std::exception &e)
			{
				std::cout << e.what() << std::endl;
				exit(0);
			}
		}


		endFrame = std::clock();
		if (this->_isPaused == false && event != E_EVENT_TYPE::RESIZE)
		{
			if (!_hasLost)
			{
				_game->handleInputs(event);
				_game->changePos();
				if (!(this->_game->update()))
					_hasLost = true;
			}
			this->_game->draw(this->_renderer, _hasLost);
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
	this->_error = ss.str();
}

const char *EngineDlsymException::what(void) const throw()
{
	return (this->_error.c_str());
}
