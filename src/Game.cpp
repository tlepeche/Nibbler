/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 20:07:14 by tiboitel          #+#    #+#             */
/*   Updated: 2017/03/30 15:08:00 by tlepeche         ###   ########.fr       */
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
	if (_width <= 100 && _height <= 80 && 10 <= _width && 10 <= _height)			
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
must be positiv numbers (10 <= width <= 100, 10 <= height <= 80)");
	}
	catch (std::exception)
	{
		throw NibblerException("Can't initiate window, width and height \
must be positiv numbers (10 <= width <= 100, 10 <= height <= 80)");
	}
}

Game::Game(Game const &rhs)
{
	*this = rhs;
}

Game::~Game()
{
}

void	Game::init(bool isMulti)
{
	_score = 0;
	std::srand(time(NULL));
	_entities.clear();
	_snakeOne.clear();
	_snakeTwo.clear();

	_snakeOne.push_back(new Snake(_width / 2, _height / 2));
	_snakeOne.push_back(new Snake(_width / 2 - 1, _height / 2));
	_snakeOne.push_back(new Snake(_width / 2 - 2, _height / 2));
	_snakeOne.push_back(new Snake(_width / 2 - 3, _height / 2));
	dynamic_cast<Snake *>((*_snakeOne.begin()))->setVectorX(1);

	if (isMulti)
	{
		_snakeTwo.push_back(new Snake(_width / 2 - 1, _height / 2 + 2));
		_snakeTwo.push_back(new Snake(_width / 2, _height / 2 + 2));
		_snakeTwo.push_back(new Snake(_width / 2 + 1, _height / 2 + 2));
		_snakeTwo.push_back(new Snake(_width / 2 + 2, _height / 2 + 2));
		dynamic_cast<Snake *>((*_snakeTwo.begin()))->setVectorX(-1);

		_entities.push_back(new Food(7, 1));
		_P2hasEaten = false;
	}
	_entities.push_back(new Food(4, 6));
	_P1hasEaten = false;
}

Game &Game::operator=(Game const &rhs)
{
	if (this != &rhs)
	{
		_entities = rhs.getEntities();
		_score = rhs.getScore();
		_width = rhs.getWidth();
		_height = rhs.getHeight(); 
		_P1hasEaten = rhs.getP1HasEaten();
		_P2hasEaten = rhs.getP2HasEaten();
		_snakeOne = rhs.getSnakeOne();
		_snakeTwo = rhs.getSnakeTwo();
	}
	return (*this);
}

std::vector<AEntity *>	Game::getEntities(void) const { return _entities; }
std::vector<AEntity *>	Game::getSnakeOne(void) const { return _snakeOne; }
std::vector<AEntity *>	Game::getSnakeTwo(void) const { return _snakeTwo; }
size_t					Game::getScore() const { return _score; }
int						Game::getWidth() const { return _width; }
int						Game::getHeight() const { return _height; }
bool					Game::getP1HasEaten() const { return _P1hasEaten; }
bool					Game::getP2HasEaten() const { return _P2hasEaten; }

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
	_entities.push_back(SF);
	return	SF;
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

void		Game::changePos(int Player)
{
	std::vector<AEntity *>	PlayerSnake;

	if (Player == 1)
		PlayerSnake = _snakeOne;
	else
		PlayerSnake = _snakeTwo;

	Snake *SnakeHead = dynamic_cast<Snake *>(*(PlayerSnake.begin()));

	std::pair <int, int> prevPos = SnakeHead->getPos();
	std::pair<int, int> newPos(SnakeHead->getPos().first + SnakeHead->getVectorX(),
			SnakeHead->getPos().second + SnakeHead->getVectorY());
	SnakeHead->setPos(newPos);
	for (std::vector<AEntity *>::iterator it = PlayerSnake.begin() + 1; it != PlayerSnake.end() ; it++)
	{
		std::pair<int, int> tmp;
		tmp = (*it)->getPos();
		(*it)->setPos(prevPos);
		prevPos = tmp;
	}
}

void	Game::handleP1Inputs(E_EVENT_TYPE &event)
{
	Snake *SnakeHead = dynamic_cast<Snake *>(*(_snakeOne.begin()));
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

void	Game::handleP2Inputs(E_EVENT_TYPE &event)
{
	Snake *SnakeHead = dynamic_cast<Snake *>(*(_snakeTwo.begin()));
	if (!SnakeHead)
		return ;
	switch (event)
	{
		case (E_EVENT_TYPE::W):
			if (SnakeHead->getVectorY() != 1)
			{
				SnakeHead->setVectorY(-1);
				SnakeHead->setVectorX(0);
			}
			break;
		case (E_EVENT_TYPE::S):
			if (SnakeHead->getVectorY() != -1)
			{
				SnakeHead->setVectorY(1);
				SnakeHead->setVectorX(0);
			}
			break;
		case (E_EVENT_TYPE::D):
			if (SnakeHead->getVectorX() != -1)
			{
				SnakeHead->setVectorY(0);
				SnakeHead->setVectorX(1);
			}
			break;
		case (E_EVENT_TYPE::A):
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

void	Game::addSquare(int Player)
{
	if (Player == 1)
	{
		_snakeOne.push_back(new Snake(_P1TailPos.first, _P1TailPos.second));
		_P1hasEaten = false;
	}
	else
	{
		_snakeTwo.push_back(new Snake(_P2TailPos.first, _P2TailPos.second));
		_P2hasEaten = false;
	}
}

E_EVENT_SOUND	Game::update(void)
{
	E_EVENT_SOUND		sound = E_EVENT_SOUND::NONE;
	std::pair<int, int>	newPos2(-1 , -1);
	Snake				*P2Head = NULL; 

	if (_P1hasEaten)
		addSquare(1);
	if (_P2hasEaten)
		addSquare(2);

	//P1 Map hit handler
	Snake *P1Head = dynamic_cast<Snake *>(*(_snakeOne.begin()));
		std::pair<int, int> newPos1(P1Head->getPos().first + P1Head->getVectorX(),
			P1Head->getPos().second + P1Head->getVectorY());
	if (newPos1.first < 0 || newPos1.first >= _width || newPos1.second < 0 || newPos1.second >= _height)
		return E_EVENT_SOUND::DEATH;

	_P1TailPos = (*(_snakeOne.end() - 1))->getPos();

	//P2 Map hit handler
	if (!(_snakeTwo.empty()))
	{
		P2Head = dynamic_cast<Snake *>(*(_snakeTwo.begin()));
		newPos2.first = P2Head->getPos().first + P2Head->getVectorX();
		newPos2.second = P2Head->getPos().second + P2Head->getVectorY();
		if (newPos2.first < 0 || newPos2.first >= _width || newPos2.second < 0 || newPos2.second >= _height)
			return E_EVENT_SOUND::DEATH;

		_P2TailPos = (*(_snakeTwo.end() - 1))->getPos();
	}


	//Food hit handler
	for (std::vector<AEntity *>::iterator it = _entities.begin(); it < _entities.end() ; it++)
	{
		if (newPos1 == (*it)->getPos())
			_P1hasEaten = true;
		else if (newPos2 == (*it)->getPos())
			_P2hasEaten = true;
		if (newPos1 == (*it)->getPos() || newPos2 == (*it)->getPos())
		{
			sound = E_EVENT_SOUND::EAT;
			Food	*Fruit = dynamic_cast<Food *>(*it);
			_score += Fruit->getScore();
			if (Fruit->getType() == E_ENTITIES_TYPE::FOOD)
				Fruit->setPos(std::rand() % _width, std::rand() % _height);
			else
				eraseEntity(Fruit);
		}
	}

	//Snake hit handler
	for (std::vector<AEntity *>::iterator it = _snakeOne.begin(); it != _snakeOne.end() ; it++)
	{
		if (((*it)->getPos() == newPos1 && P1Head != *it) ||
			   	(P2Head && (*it)->getPos() == newPos2 && *it != P2Head))
			return E_EVENT_SOUND::DEATH;
	}
	if (!_snakeTwo.empty())
	{
		for (std::vector<AEntity *>::iterator it = _snakeTwo.begin(); it != _snakeTwo.end() ; it++)
		{
			if (((*it)->getPos() == newPos1 && P1Head != *it) ||
					(P2Head && (*it)->getPos() == newPos2 && *it != P2Head))
				return E_EVENT_SOUND::DEATH;
		}
	}
	return sound;
}



void	Game::draw(IRenderer *renderer, bool hasLost)
{
	renderer->clearScreen();
	//P1
	renderer->drawP1SnakeHead(dynamic_cast<Snake *>(*(_snakeOne.begin())));
	for (std::vector <AEntity *>::iterator it = _snakeOne.begin() + 1; it != _snakeOne.end(); it++)
		renderer->drawP1Snake(dynamic_cast<Snake *>(*it));
	//P2
	if (!_snakeTwo.empty())
	{
		renderer->drawP2SnakeHead(dynamic_cast<Snake *>(*(_snakeTwo.begin())));
		for (std::vector <AEntity *>::iterator it = _snakeTwo.begin() + 1; it != _snakeTwo.end(); it++)
			renderer->drawP2Snake(dynamic_cast<Snake *>(*it));
	}
	for (std::vector <AEntity *>::iterator it = _entities.begin(); it != _entities.end(); it++)
	{
		renderer->drawScore(_score);
		if ((*it)->getType() == E_ENTITIES_TYPE::FOOD)
			renderer->drawFood(dynamic_cast<Food *>(*it));
		if ((*it)->getType() == E_ENTITIES_TYPE::SPECIALFOOD)
			renderer->drawSpecFood(dynamic_cast<SpecialFood *>(*it));
	}
	if (hasLost)
		renderer->drawGO();
	renderer->render();
}

void	Game::close()
{
	_entities.clear();	
}
