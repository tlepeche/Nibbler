/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 20:07:14 by tiboitel          #+#    #+#             */
/*   Updated: 2017/03/06 17:40:23 by tiboitel         ###   ########.fr       */
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
	_entities.clear();
	_entities.push_back(new Snake(1, 1));
	_entities.push_back(new Snake(2, 1));
	_entities.push_back(new Snake(3, 1));
	_entities.push_back(new Snake(4, 1));
	_entities.push_back(new Food(18, 1));
	_entities.push_back(new Food(4, 7));

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

int						Game::addEntities(AEntity *entity)
{
	_entities.push_back(entity);
	return (1);
}

void					Game::handleInputs(E_EVENT_TYPE &event)
{
	(void)event;
}

void					Game::update(void)
{
	Snake *SnakeHead = dynamic_cast<Snake *>(*(_entities.begin()));
	if (!SnakeHead)
		std::cout << "NULL" << std::endl;
	bool hit = false;
	for (std::vector<AEntity *>::iterator it = _entities.begin() ; it != _entities.end() ; it++)
	{
		if (SnakeHead->hasHit(**it) && !hit) // == la tete a hit un truc
		{
			//on a hit un fruit -> passage bool a true et attente de le depasser pour add une case au snake
			if ((*it)->getType() == E_ENTITIES_TYPE::FOOD)
				hit = true;
			// on a hit autre chose (wall ou snake) du coup GAME OVER
			else
			{
				std::cout << "GAME OVER" << std::endl;
				return ;
			}
		}
		//on est 1 tick apres que la queue ait depasse la case fruit
		//	 -> on add une case au snake a l'endroit ou etait le fruit
		if (hit && (*it)->getType() == E_ENTITIES_TYPE::FOOD && !SnakeHead->hasHit(**it)) //condition a modifier
		{
			//	on change le type de FOOD en SNAKE, la position est deja bonne;
			//	-> evite de creer une entite SNAKE et delete l'entite FOOD
			(*it)->setType(E_ENTITIES_TYPE::SNAKE);
			hit = false;
		}
	}
}

void					Game::draw(IRenderer *renderer)
{
	renderer->clearScreen();
	for (std::vector <AEntity *>::iterator it = _entities.begin(); it != _entities.end();
			it++)
	{
		if ((*it)->getType() == E_ENTITIES_TYPE::SNAKE)
			renderer->drawSnake(dynamic_cast<Snake *>(*it));
		if ((*it)->getType() == E_ENTITIES_TYPE::FOOD)
			renderer->drawFood(dynamic_cast<Food *>(*it));
	}
	renderer->render();
}
