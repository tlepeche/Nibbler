/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Engine.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 22:09:17 by tiboitel          #+#    #+#             */
/*   Updated: 2017/03/23 19:00:57 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Engine.hpp>
#include <unistd.h>

Engine::Engine()
{
}

Engine::Engine(char *width, char *height, bool debug): _hasLost(false), _handler(NULL), _debug(debug)
{
	_audio_handler = NULL;
	_game = new Game(width, height);
	setRenderer("sfml/sfml_renderer.so");
	setAudioDevice("audio/sdl_audio.so");
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
		_audio_device = rhs.getAudioDevice();
	}
	return (*this);
}

bool			Engine::getIsPaused() const { return _isPaused; }
bool			Engine::getHasLost() const { return _hasLost; }
bool			Engine::getDebug() const { return _debug; }
Game			*Engine::getGame() const { return _game; }
IRenderer		*Engine::getRenderer() const { return _renderer; }
IAudioDevice	*Engine::getAudioDevice() const { return _audio_device; }
void			*Engine::getHandler() const { return _handler; }

Engine::~Engine()
{
	delete _renderer;
	if (dlclose(_handler) != 0)
		throw NibblerException("Unable to close handler.");
	delete _game;
}

void	Engine::setAudioDevice(const char *DLPath)
{
	IAudioDevice	*(*create_audiodevice)();
	
	if (_audio_handler != NULL)
	{
		_audio_device->close();
		if (dlclose(_audio_handler) != 0)
			throw EngineDlsymException("Unable to close handler. Error", dlerror(), DLPath);
		_audio_handler = NULL;
	}
	_audio_handler = dlopen(DLPath, RTLD_LAZY);
	if (!_audio_handler)
		throw EngineDlsymException("Unable to dlopen. Error:", dlerror(), DLPath);
	create_audiodevice = reinterpret_cast<IAudioDevice * (*)()>(dlsym(_audio_handler, "create_audiodevice"));
	if (!create_audiodevice)
		throw EngineDlsymException("Unable to find symbol. Error", dlerror(),
				DLPath);
	_audio_device = create_audiodevice();
	if (!_audio_device->init())
		throw NibblerException("Unable to initialize dynamic audio device.");
	(void)DLPath;
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

void	Engine::handleLibChange(E_EVENT_TYPE const &event)
{
	if (event == E_EVENT_TYPE::LOAD_LIBRARY_ONE)
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
}

void Engine::handleGame(void)
{
	E_EVENT_TYPE		event;
	double				frameRate;
	std::clock_t		deltaTime;
	std::clock_t		endFrame;

	while (true)
	{
		frameRate = 10;
		if (std::rand() % 100 == 1 && !(_game->getSpeFood()) && !_hasLost)
			_game->addSpecialFood();
		std::clock_t startFrame = std::clock();
		event = _renderer->getLastEvent();
		if (event == E_EVENT_TYPE::QUIT)
		{
			_renderer->close();
			_game->close();
			return ;
		}
		else if (event == E_EVENT_TYPE::RESTART)
		{
			_hasLost = false;
			_game->init();
		}
		else if (event == E_EVENT_TYPE::SPACE && _debug)
			_game->addSquare();
		handleLibChange(event);
		endFrame = std::clock();
		if (_isPaused == false && event != E_EVENT_TYPE::RESIZE)
		{
			_game->handleInputs(event);
			if (!_hasLost && !(_game->update()))
				_hasLost = true;
			if (!_hasLost)
				_game->changePos();
			_game->draw(_renderer, _hasLost);
		}
		deltaTime = endFrame - startFrame;
		while (((deltaTime / (double)CLOCKS_PER_SEC) * 1000.0) < (1000.0 / frameRate))
		{
			endFrame = std::clock();
			deltaTime = endFrame - startFrame;
		}

		SpecialFood	*speFood = _game->getSpeFood();
		if (speFood && !_hasLost)
		{
			speFood->setLifeSpan(deltaTime);
			if (speFood->getLifeSpan() == 0)
				_game->eraseEntity(speFood);
		}
		frameRate += speFood != NULL ? (_game->getEntities().size() - 6) / 2 : (_game->getEntities().size() - 5) / 2;
		if (frameRate > 60)
			frameRate = 60;
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
