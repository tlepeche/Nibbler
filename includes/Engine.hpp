/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Engine.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 22:02:07 by tiboitel          #+#    #+#             */
/*   Updated: 2017/03/23 18:26:36 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ENGINE_HPP
# define FT_ENGINE_HPP

#include <ctime>
#include <dlfcn.h>
#include <Game.hpp>
#include <Exception.hpp>
#include <IRenderer.hpp>
#include <SpecialFood.hpp>
#include <IAudioDevice.hpp>

class Engine
{
	public:	
		Engine(char	*width, char *height, bool debug = false);
		~Engine();
		Engine			(const Engine &rhs);
		Engine			&operator=(Engine const &rhs);
		bool			init(void);
		void			handleGame(void);
		void			setRenderer(const char *DLPath);
		void			setAudioDevice(const char *DLPath);
		bool			getIsPaused() const;
		bool			getHasLost() const;
		bool			getDebug() const;
		Game			*getGame() const;
		IRenderer		*getRenderer() const;
		void			*getHandler() const;
		IAudioDevice	*getAudioDevice() const;
		void			handleLibChange(E_EVENT_TYPE const &event);

	private:
		Engine();
		void			draw();

		bool			_isPaused;
		bool			_hasLost;
		Game			*_game;
		IRenderer		*_renderer;
		IAudioDevice	*_audio_device;
		void			*_audio_handler;
		void			*_handler;
		bool			_debug;
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
