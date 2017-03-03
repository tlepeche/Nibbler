/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Renderer.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 15:55:13 by tiboitel          #+#    #+#             */
/*   Updated: 2017/03/03 18:06:41 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_RENDERER_HPP
# define FT_RENDERER_HPP

#include "IRenderer.hpp"
#include <SDL2/SDL.h>
#include <iostream>

class SDLRenderer : public IRenderer
{
	public:
		SDLRenderer();
		~SDLRenderer();
		bool 			init(int windw_w, int windw_h);
		bool 			close(void);
		E_EVENT_TYPE	getLastEvent(void);
	private:
		SDL_Window		*_window;
		SDL_Renderer	*_renderer;
		SDL_Surface		*_screen;
		SDL_Event		_event;
};

extern "C"
{
	IRenderer	*create_renderer()
	{
		return (new SDLRenderer());
	}
}
#endif
