/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 20:07:14 by tiboitel          #+#    #+#             */
/*   Updated: 2017/03/08 19:41:05 by tlepeche         ###   ########.fr       */
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

void	Game::init(void)
{
	_score = 0;
	std::srand(time(NULL));
	_entities.clear();
	//snake pop au milieu de lecran (cf consigne)
	_entities.push_back(new Snake(43, 30));
	_entities.push_back(new Snake(43 - 1, 30));
	_entities.push_back(new Snake(43 - 2, 30));
	_entities.push_back(new Snake(43 - 3, 30));
	_entities.push_back(new Food(4, 7));
	dynamic_cast<Snake *>((*_entities.begin()))->setVectorY(1);
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

size_t					Game::getScore() const { return _score; }

void					Game::setScore(size_t score)
{
	_score = score;
}

SpecialFood					*Game::addSpecialFood()
{
	SpecialFood	*SF = new SpecialFood(std::rand() % 86, std::rand() % 60, 1000, 10000);
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
	for (std::vector<AEntity *>::iterator it = _entities.begin() + 1; it != _entities.end() ; it++)
	{
		if (*it == entity)
		{
			std::cout << "ERASE" << std::endl;
			delete (*it);
			_entities.erase(it);
			std::cout << "DONE" << std::endl;
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

bool					Game::update(void)
{
	Snake	*SnakeHead = dynamic_cast<Snake *>(*(_entities.begin()));
	Snake	*Tail;
	Food	*Fruit;
	if (!SnakeHead)
	{
		std::cout << "SNAKEHEAD" << std::endl;
		return false;
	}
	bool hit = false;
	for (std::vector<AEntity *>::iterator it = _entities.begin(); it != _entities.end() ; it++)
	{
		if (SnakeHead->hasHit(**it)) // == la tete a hit un truc
		{
			if ((*it)->getType() == E_ENTITIES_TYPE::FOOD || (*it)->getType() == E_ENTITIES_TYPE::SPECIALFOOD)
			{
				hit = true;
				Fruit = dynamic_cast<Food *>(*it);
				_score += Fruit->getScore();
			}
			else
				return false;
		}
		if ((*it)->getType() == E_ENTITIES_TYPE::SNAKE)
			Tail = dynamic_cast<Snake *>(*it);
	}
	// on change la position du fruit et on ajoute une case au snake
	if (hit)
	{
		std::pair<int, int> newTailPos(Tail->getPos().first + Tail->getVectorX(),
				Tail->getPos().second + Tail->getVectorY());
		_entities.push_back(new Snake(newTailPos.first, newTailPos.second));
		Fruit->setPos(std::rand() % (86), std::rand() % (60));
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
			renderer->drawSnake(dynamic_cast<Snake *>(*it));
		if ((*it)->getType() == E_ENTITIES_TYPE::FOOD)
			renderer->drawFood(dynamic_cast<Food *>(*it));
	   	if( (*it)->getType() == E_ENTITIES_TYPE::SPECIALFOOD)
			renderer->drawSpecFood(dynamic_cast<SpecialFood *>(*it));
		if (hasLost)
			renderer->drawGO();
	}
	renderer->render();
}
