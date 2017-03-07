/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Engine.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 22:02:07 by tiboitel          #+#    #+#             */
/*   Updated: 2017/03/07 16:26:28 by tlepeche         ###   ########.fr       */
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
		void		handleGame(void);
		void		setRenderer(const char *DLPath);
	private:
		Engine();
		bool		_isPaused;
		bool		_hasLost;
		void		draw();
		Game		*_game;
		IRenderer	*_renderer;
		void		*_handler;
};

class EngineDlsymException : public NibblerException
{
	public:
		EngineDlsymException(const char *msg, const char *dlerror, const char
			*library_path);
		virtual ~EngineDlsymException() throw () {};
		virtual const char	*what(void) const throw();
	private:
		EngineDlsymException();
};
#endif
