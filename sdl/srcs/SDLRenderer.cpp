/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SDLRenderer.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 15:55:04 by tiboitel          #+#    #+#             */
/*   Updated: 2017/03/04 19:34:22 by tiboitel         ###   ########.fr       */
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
		case SDL_KEYDOWN:
			if (_event.key.keysym.sym == SDLK_UP)
				return (E_EVENT_TYPE::UP);
			if (_event.key.keysym.sym == SDLK_DOWN)
				return (E_EVENT_TYPE::DOWN);
			if (_event.key.keysym.sym == SDLK_LEFT)
				return (E_EVENT_TYPE::LEFT);
			if (_event.key.keysym.sym == SDLK_RIGHT)
					return (E_EVENT_TYPE::RIGHT);
		break;
		default:
			return (E_EVENT_TYPE::UNKNOWN);
			break;
	}
	return (E_EVENT_TYPE::UNKNOWN);
}

void	SDLRenderer::render(void) const
{
	SDL_RenderPresent(_renderer);
}

void	SDLRenderer::drawSnake(Snake *snake) const
{
	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
	SDL_Rect		r;

	r.x = snake->getPos().first;
	r.y = snake->getPos().second;
	r.h = 16;
	r.w = 16;
	SDL_RenderFillRect(_renderer, &r);
}

void	SDLRenderer::drawFood(Food *food) const
{
	SDL_SetRenderDrawColor(_renderer, 255, 255, 0, 255);
	SDL_Rect		r;

	r.x = food->getPos().first;
	r.y = food->getPos().second;
	r.h = 16;
	r.w = 16;
	SDL_RenderFillRect(_renderer, &r);
}

void	SDLRenderer::clear(void) const
{
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
	SDL_RenderClear(_renderer);
}

bool SDLRenderer::close()
{
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	return (false);
}
