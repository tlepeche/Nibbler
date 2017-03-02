/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 20:02:09 by tiboitel          #+#    #+#             */
/*   Updated: 2017/03/02 17:32:04 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GAME_HPP
# define FT_GAME_HPP

#include <vector>
#include <AEntity.hpp>
#include <Snake.hpp>

class Game
{
	public:
		Game();
		~Game();
		void					init();
		void					start();
		Game					(const Game &rhs);
		Game 					&operator=(Game const &rhs);
		std::vector<AEntity *>	getEntities() const;
		int						addEntities(AEntity *entity);
		unsigned int			countEntities(void);
		void					update(void);

	private:
		std::vector<AEntity *>	_entities;		
};

#endif
