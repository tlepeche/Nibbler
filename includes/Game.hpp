/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 20:02:09 by tiboitel          #+#    #+#             */
/*   Updated: 2017/03/08 16:59:31 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GAME_HPP
# define FT_GAME_HPP

#include <vector>
#include <IRenderer.hpp>
#include <AEntity.hpp>
#include <Snake.hpp>
#include <Food.hpp>
#include <Exception.hpp>

class Game
{
	public:
		Game();
		~Game();
		void					init();
		Game					(const Game &rhs);
		Game 					&operator=(Game const &rhs);
		std::vector<AEntity *>	getEntities() const;
		size_t					getScore() const;
		int						addEntities(AEntity *entity);
		bool					update(void);
		void					draw(IRenderer *renderer, bool hasLost);

		std::pair<int, int>		changePos(AEntity * entity, std::pair<int, int> newPos);
		void					handleInputs(E_EVENT_TYPE &event);
		void					setScore(size_t score);

	private:
		std::vector<AEntity *>	_entities;		
		size_t					_score;
		std::pair<int, int>		_tmpVector;
};

#endif
