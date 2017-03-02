/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Engine.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 22:02:07 by tiboitel          #+#    #+#             */
/*   Updated: 2017/03/02 22:35:04 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ENGINE_HPP
# define FT_ENGINE_HPP

#include <Game.hpp>

class Engine
{
	public:	
		Engine();
		~Engine();
		Engine		(const Engine &rhs);
		Engine		&operator=(Game const &rhs);
		bool		init(void);
		void		handle_game(void);
	private:
		void		draw();
		Game		*_game;
};

#endif
