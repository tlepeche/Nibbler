/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 20:02:09 by tiboitel          #+#    #+#             */
/*   Updated: 2017/03/23 18:36:22 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GAME_HPP
# define FT_GAME_HPP

#include <vector>
#include <IRenderer.hpp>
#include <AEntity.hpp>
#include <Snake.hpp>
#include <Food.hpp>
#include <SpecialFood.hpp>
#include <Exception.hpp>

class Game
{
	public:
		Game();
		~Game();
		Game(char *w, char *h);
		void					init(bool isMulti);
		bool					check(std::string w, std::string h);
		Game					(const Game &rhs);
		Game 					&operator=(Game const &rhs);

		std::vector<AEntity *>	getEntities() const;
		std::vector<AEntity *>	getSnakeOne() const;
		std::vector<AEntity *>	getSnakeTwo() const;
		size_t					getScore() const;
		int						getWidth() const;
		int						getHeight() const;
		SpecialFood				*getSpeFood();
		bool					getP2HasEaten() const;
		bool					getP1HasEaten() const;
		void					close();

		bool					hasHit(AEntity &Head, AEntity &src);
		SpecialFood				*addSpecialFood();
		void					eraseEntity(AEntity *entity);
		bool					update(void);
		void					draw(IRenderer *renderer, bool hasLost);

		void					addSquare(int Player);
		void					changePos(int Player);
		void					handleP1Inputs(E_EVENT_TYPE &event);
		void					handleP2Inputs(E_EVENT_TYPE &event);
		void					setScore(size_t score);

	private:
		std::vector<AEntity *>	_entities;
		std::vector<AEntity *>	_snakeOne;
		std::vector<AEntity *>	_snakeTwo;
		size_t					_score;
		int						_width;
		int						_height;
		bool					_P1hasEaten;
		bool					_P2hasEaten;
		std::pair<int, int>		_P1TailPos;
		std::pair<int, int>		_P2TailPos;
};

#endif
