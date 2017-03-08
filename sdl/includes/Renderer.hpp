/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Renderer.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 15:55:13 by tiboitel          #+#    #+#             */
/*   Updated: 2017/03/08 15:38:47 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_RENDERER_HPP
# define FT_RENDERER_HPP

#include <SDL2/SDL.h>
#include <iostream>
#include "IRenderer.hpp"
#include "Snake.hpp"
#include "Food.hpp"

#define SQUARE_LEN 16
class SDLRenderer : public IRenderer
{
	public:
		SDLRenderer();
		~SDLRenderer();
		bool 			init(int windw_w, int windw_h);
		bool 			close(void);
		void			render(void) const;
		void			clearScreen(void) const;
		void			drawSnake(Snake *snake) const;
		void			drawFood(Food *food) const;
		void			drawGO() const;
		void			drawScore(size_t score) const;
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
