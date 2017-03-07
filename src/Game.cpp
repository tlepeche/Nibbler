/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 20:07:14 by tiboitel          #+#    #+#             */
/*   Updated: 2017/03/07 21:31:45 by tlepeche         ###   ########.fr       */
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
	_entities.push_back(new Snake(1380 / 32, 960 / 32));
	_entities.push_back(new Snake(1380 / 32 - 1, 960 / 32));
	_entities.push_back(new Snake(1380 / 32 - 2, 960 / 32));
	_entities.push_back(new Snake(1380 / 32 - 3, 960 / 32));
	_entities.push_back(new Food(4, 7));
	dynamic_cast<Snake *>((*_entities.begin()))->setVectorX(1);
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

int						Game::addEntities(AEntity *entity)
{
	_entities.push_back(entity);
	return (1);
}

std::pair<int, int>		Game::changePos(AEntity *entity, std::pair<int, int> newPos)
{
	if (entity->getType() == E_ENTITIES_TYPE::SNAKE)
	{
		std::pair<int, int> tmp;
		tmp = entity->getPos();
		entity->setPos(newPos);
		return tmp;
	}
	return newPos;
}

void					Game::handleInputs(E_EVENT_TYPE &event)
{
	Snake *SnakeHead = dynamic_cast<Snake *>(*(_entities.begin()));
	// First: chercher si la direction a changee
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
	//Deplacement de la tete du snake et de toutes les autres entites snakes
	std::pair<int, int> tmp(0, 0);
	tmp = SnakeHead->getPos();

	std::pair<int, int> newPos(SnakeHead->getPos().first + SnakeHead->getVectorX(),
			SnakeHead->getPos().second + SnakeHead->getVectorY());
	if (newPos != tmp)
	{
		SnakeHead->setPos(newPos);
		for (std::vector<AEntity *>::iterator it = _entities.begin() + 1; it != _entities.end() ; it++)
			tmp = changePos(*it, tmp);
	}
}

bool					Game::update(void)
{
	Snake	*SnakeHead = dynamic_cast<Snake *>(*(_entities.begin()));
	Snake	*Tail;
	Food	*Fruit;
	if (!SnakeHead)
		return false;
	bool hit = false;
	for (std::vector<AEntity *>::iterator it = _entities.begin() ; it != _entities.end() ; it++)
	{
		if (SnakeHead->hasHit(**it) && !hit) // == la tete a hit un truc
		{
			if ((*it)->getType() == E_ENTITIES_TYPE::FOOD)
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
		Fruit->setPos(std::rand() % (1380/16), std::rand() % (960/16));
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
		if (hasLost)
			renderer->drawGO();
	}
	renderer->render();
}
