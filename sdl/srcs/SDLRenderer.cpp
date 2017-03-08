/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SDLRenderer.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 15:55:04 by tiboitel          #+#    #+#             */
/*   Updated: 2017/03/08 19:40:26 by tlepeche         ###   ########.fr       */
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
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cerr << SDL_GetError() << std::endl;
		return (false);
	}
	_window = SDL_CreateWindow("Nibbler", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, windw_w * SQUARE_LEN, windw_h * SQUARE_LEN, SDL_WINDOW_SHOWN);
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED |
			SDL_RENDERER_PRESENTVSYNC);
	if (!_renderer)
	{
		std::cerr << SDL_GetError()  << std::endl;
		return  (false);
	}
	_screen = SDL_CreateRGBSurface(0, windw_w * SQUARE_LEN, windw_h * SQUARE_LEN, 32, 0, 0, 0, 0);
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
			if (_event.key.keysym.sym == SDLK_ESCAPE)
				return (E_EVENT_TYPE::QUIT);
			if (_event.key.keysym.sym == SDLK_1)
				return (E_EVENT_TYPE::LOAD_LIBRARY_ONE);
			if (_event.key.keysym.sym == SDLK_2)
				return (E_EVENT_TYPE::LOAD_LIBRARY_TWO);
			if (_event.key.keysym.sym == SDLK_3)
				return (E_EVENT_TYPE::LOAD_LIBRARY_THREE);
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

	r.x = snake->getPos().first * SQUARE_LEN;
	r.y = snake->getPos().second * SQUARE_LEN;
	r.h = SQUARE_LEN;
	r.w = SQUARE_LEN;
	SDL_RenderFillRect(_renderer, &r);
}

void	SDLRenderer::drawFood(Food *food) const
{
	SDL_SetRenderDrawColor(_renderer, 255, 255, 0, 255);
	SDL_Rect		r;

	r.x = food->getPos().first * SQUARE_LEN;
	r.y = food->getPos().second * SQUARE_LEN;
	r.h = SQUARE_LEN;
	r.w = SQUARE_LEN;
	SDL_RenderFillRect(_renderer, &r);
}

void	SDLRenderer::drawSpecFood(SpecialFood *food) const
{
	SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255);
	SDL_Rect		r;

	r.x = food->getPos().first * SQUARE_LEN;
	r.y = food->getPos().second * SQUARE_LEN;
	r.h = SQUARE_LEN;
	r.w = SQUARE_LEN;
	SDL_RenderFillRect(_renderer, &r);
}

void	SDLRenderer::drawScore(size_t score) const
{ 	
	//Pour ecrire text, need SDL_tff;
	(void)score;
}

void	SDLRenderer::drawGO() const
{
	//Pour ecrire text, need SDL_tff;
	return;
}

void	SDLRenderer::clearScreen(void) const
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
