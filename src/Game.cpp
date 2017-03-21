/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 20:07:14 by tiboitel          #+#    #+#             */
/*   Updated: 2017/03/21 17:43:40 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Game.hpp>
#include <regex>
#include <string>

bool	Game::check(std::string w, std::string h)
{
	_width = std::stoul(w);
	_height = std::stoul(h);

	if (!(std::regex_match(w, std::regex("[0-9]+")) && std::regex_match(h, std::regex("[0-9]+"))))
		return false;
	if (_width <= 100 && _height <= 80 && 5 <= _width && 5 <= _height)			
		return true;
	return false;
}

Game::Game(char *width, char *height)
{
	std::string w(width);
	std::string h(height);
	try
	{
	if (!(check(w, h)))
		throw NibblerException("Can't initiate window, width and height \
must be positiv numbers (5 <= width <= 100, 5 <= height <= 80)");
	}
	catch (std::exception)
	{
		throw NibblerException("Can't initiate window, width and height \
must be positiv numbers (5 <= width <= 100, 5 <= height <= 80)");
	}
}

Game::Game(Game const &rhs)
{
	*this = rhs;
}

Game::~Game()
{
}

void	Game::init(void)
{
	_score = 0;
	std::srand(time(NULL));
	_entities.clear();
	_entities.push_back(new Snake(_width / 2, _height / 2));
	_entities.push_back(new Snake(_width / 2 - 1, _height / 2));
	_entities.push_back(new Snake(_width / 2 - 2, _height / 2));
	_entities.push_back(new Snake(_width / 2 - 3, _height / 2));
	_entities.push_back(new Food(4, 4));
	dynamic_cast<Snake *>((*_entities.begin()))->setVectorX(1);
	_hasEaten = false;
}

Game &Game::operator=(Game const &rhs)
{
	if (this != &rhs)
	{
		_entities = rhs.getEntities();
		_score = rhs.getScore();
		_width = rhs.getWidth();
		_height = rhs.getHeight(); 
		_hasEaten = rhs.getHasEaten();
	}
	return (*this);
}

std::vector<AEntity *>	Game::getEntities(void) const { return _entities; }

size_t					Game::getScore() const { return _score; }

int						Game::getWidth() const { return _width; }

int						Game::getHeight() const { return _height; }

bool					Game::getHasEaten() const { return _hasEaten; }

SpecialFood				*Game::getSpeFood()
{
	for (std::vector<AEntity *>::iterator it = _entities.begin(); it != _entities.end() ; it++)
	{
		if ((*it)->getType() == E_ENTITIES_TYPE::SPECIALFOOD)
			return (dynamic_cast<SpecialFood *>(*it));
	}
	return NULL;	
}

void					Game::setScore(size_t score)
{
	_score = score;
}

SpecialFood					*Game::addSpecialFood()
{
	SpecialFood	*SF = new SpecialFood(std::rand() % _width, std::rand() % _height, 1000, 5000000);
	addEntities(SF);
	return	SF;
}

int						Game::addEntities(AEntity *entity)
{
	_entities.push_back(entity);
	return (1);
}

void					Game::eraseEntity(AEntity *entity)
{
	for (std::vector<AEntity *>::iterator it = _entities.begin(); it != _entities.end() ; it++)
	{
		if (*it == entity)
		{
			delete (*it);
			_entities.erase(it);
			break;
		}
	}
}

void		Game::changePos()
{
	Snake *SnakeHead = dynamic_cast<Snake *>(*(_entities.begin()));

	std::pair <int, int> prevPos = SnakeHead->getPos();
	std::pair<int, int> newPos(SnakeHead->getPos().first + SnakeHead->getVectorX(),
			SnakeHead->getPos().second + SnakeHead->getVectorY());
	SnakeHead->setPos(newPos);
	for (std::vector<AEntity *>::iterator it = _entities.begin() + 1; it != _entities.end() ; it++)
	{
		if ((*it)->getType() == E_ENTITIES_TYPE::SNAKE)
		{
			std::pair<int, int> tmp;
			tmp = (*it)->getPos();
			(*it)->setPos(prevPos);
			prevPos = tmp;
		}
	}
}

void					Game::handleInputs(E_EVENT_TYPE &event)
{
	Snake *SnakeHead = dynamic_cast<Snake *>(*(_entities.begin()));
	if (!SnakeHead)
		return ;
	switch (event)
	{
		case (E_EVENT_TYPE::UP):
			if (SnakeHead->getVectorY() != 1)
		{
			SnakeHead->setVectorY(-1);
			SnakeHead->setVectorX(0);
		}
			break;
		case (E_EVENT_TYPE::DOWN):
			if (SnakeHead->getVectorY() != -1)
		{
			SnakeHead->setVectorY(1);
			SnakeHead->setVectorX(0);
		}
			break;
		case (E_EVENT_TYPE::RIGHT):
			if (SnakeHead->getVectorX() != -1)
		{
			SnakeHead->setVectorY(0);
			SnakeHead->setVectorX(1);
		}
			break;
		case (E_EVENT_TYPE::LEFT):
			if (SnakeHead->getVectorX() != 1)
		{
			SnakeHead->setVectorY(0);
			SnakeHead->setVectorX(-1);
		}
			break;
		default:
			break;
	}
}

void	Game::addSquare()
{
	_entities.push_back(new Snake(_TailPos.first, _TailPos.second));
	_hasEaten = false;
}

bool	Game::update(void)
{
	Food	*Fruit;
	if (_hasEaten)
		addSquare();

	Snake *SnakeHead = dynamic_cast<Snake *>(*(_entities.begin()));
	std::pair<int, int> newPos(SnakeHead->getPos().first + SnakeHead->getVectorX(),
			SnakeHead->getPos().second + SnakeHead->getVectorY());

	if (newPos.first < 0 || newPos.first >= _width || newPos.second < 0 || newPos.second >= _height)
		return false;
	for (std::vector<AEntity *>::iterator it = _entities.begin() + 1; it != _entities.end() ; it++)
	{
		if (newPos == (*it)->getPos())
		{
			if ((*it)->getType() == E_ENTITIES_TYPE::FOOD || (*it)->getType() == E_ENTITIES_TYPE::SPECIALFOOD)
			{
				_hasEaten = true;
				Fruit = dynamic_cast<Food *>(*it);
				_score += Fruit->getScore();
				if (Fruit->getType() == E_ENTITIES_TYPE::FOOD)
					Fruit->setPos(std::rand() % _width, std::rand() % _height);
				else
					eraseEntity(Fruit);
			}
			else
				return false;
		}
		if ((*it)->getType() == E_ENTITIES_TYPE::SNAKE)
			_TailPos = (*it)->getPos();
	}
	return true;
}

void					Game::draw(IRenderer *renderer, bool hasLost)
{
	renderer->clearScreen();
	for (std::vector <AEntity *>::iterator it = _entities.begin(); it != _entities.end();
			it++)
	{
		renderer->drawScore(_score);
		if ((*it)->getType() == E_ENTITIES_TYPE::SNAKE)
		{
			if (it == _entities.begin())
				renderer->drawSnakeHead(dynamic_cast<Snake *>(*it));
			else
				renderer->drawSnake(dynamic_cast<Snake *>(*it));
		}
		if ((*it)->getType() == E_ENTITIES_TYPE::FOOD)
			renderer->drawFood(dynamic_cast<Food *>(*it));
	   	if( (*it)->getType() == E_ENTITIES_TYPE::SPECIALFOOD)
			renderer->drawSpecFood(dynamic_cast<SpecialFood *>(*it));
		if (hasLost)
			renderer->drawGO();
	}
	renderer->render();
}
