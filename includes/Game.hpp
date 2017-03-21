/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 20:02:09 by tiboitel          #+#    #+#             */
/*   Updated: 2017/03/21 18:52:28 by tlepeche         ###   ########.fr       */
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
		void					init();
		bool					check(std::string w, std::string h);
		Game					(const Game &rhs);
		Game 					&operator=(Game const &rhs);

		std::vector<AEntity *>	getEntities() const;
		size_t					getScore() const;
		int						getWidth() const;
		int						getHeight() const;
		SpecialFood				*getSpeFood();
		bool					getHasEaten() const;
		void					close();

		bool					hasHit(AEntity &Head, AEntity &src);
		int						addEntities(AEntity *entity);
		SpecialFood				*addSpecialFood();
		void					eraseEntity(AEntity *entity);
		bool					update(void);
		void					draw(IRenderer *renderer, bool hasLost);

		void					addSquare();
		void					changePos();
		void					handleInputs(E_EVENT_TYPE &event);
		void					setScore(size_t score);

	private:
		std::vector<AEntity *>	_entities;		
		size_t					_score;
		int						_width;
		int						_height;
		bool					_hasEaten;
		std::pair<int, int>		_TailPos;
};

#endif
