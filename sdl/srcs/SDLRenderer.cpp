/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SDLRenderer.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 15:55:04 by tiboitel          #+#    #+#             */
/*   Updated: 2017/03/03 18:05:38 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Renderer.hpp"

SDLRenderer::SDLRenderer()
{
}

SDLRenderer::~SDLRenderer()
{
}

bool SDLRenderer::init(int windw_w, int windw_h)
{
	(void)windw_w;
	(void)windw_h;
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cerr << SDL_GetError() << std::endl;
		return (false);
	}
	_window = SDL_CreateWindow("Nibbler", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, windw_w, windw_h, SDL_WINDOW_SHOWN);
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED |
			SDL_RENDERER_PRESENTVSYNC);
	if (!_renderer)
	{
		std::cerr << SDL_GetError()  << std::endl;
		return  (false);
	}
	_screen = SDL_CreateRGBSurface(0, windw_w, windw_h, 32, 0, 0, 0, 0);
	return (true);
}

E_EVENT_TYPE	SDLRenderer::getLastEvent(void)
{
	SDL_PollEvent(&_event);
	switch (_event.type)
	{
		case SDL_QUIT:
			return (E_EVENT_TYPE::QUIT);
			break;
		default:
			return (E_EVENT_TYPE::UNKNOWN);
			break;
	}
}

bool SDLRenderer::close()
{
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	return (false);
}
