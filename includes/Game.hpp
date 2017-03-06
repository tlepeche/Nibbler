/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 20:02:09 by tiboitel          #+#    #+#             */
/*   Updated: 2017/03/06 17:19:29 by tiboitel         ###   ########.fr       */
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
		int						addEntities(AEntity *entity);
		void					update(void);
		void					draw(IRenderer *renderer);
		void					handleInputs(E_EVENT_TYPE &event);
	private:
		std::vector<AEntity *>	_entities;		
};

#endif
