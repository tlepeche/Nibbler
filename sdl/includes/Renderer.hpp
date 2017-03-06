/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Renderer.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 15:55:13 by tiboitel          #+#    #+#             */
/*   Updated: 2017/03/06 17:24:43 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_RENDERER_HPP
# define FT_RENDERER_HPP

#include <SDL2/SDL.h>
#include <iostream>
#include "IRenderer.hpp"
#include "Snake.hpp"
#include "Food.hpp"

class SDLRenderer : public IRenderer
{
	public:
		SDLRenderer();
		~SDLRenderer();
		bool 			init(int windw_w, int windw_h);
		bool 			close(void);
		bool			render(void) const;
		void			clearScreen(void) const;
		void			drawSnake(Snake *snake) const;
		void			drawFood(Food *food) const;
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
