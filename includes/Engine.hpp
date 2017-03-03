/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Engine.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 22:02:07 by tiboitel          #+#    #+#             */
/*   Updated: 2017/03/03 19:23:31 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ENGINE_HPP
# define FT_ENGINE_HPP

#include <ctime>
#include <dlfcn.h>
#include <Game.hpp>
#include <Exception.hpp>
#include <IRenderer.hpp>
# define MS_PER_UPDATE 1

class Engine
{
	public:	
		Engine(char *DLpath);
		~Engine();
		Engine		(const Engine &rhs);
		Engine		&operator=(Engine const &rhs);
		bool		init(void);
		void		handle_game(void);
	private:
		Engine();
		void		draw();
		Game		*_game;
		IRenderer	*_renderer;
		void		*_handler;
};

#endif
