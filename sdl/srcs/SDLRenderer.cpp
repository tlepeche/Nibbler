/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SDLRenderer.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 15:55:04 by tiboitel          #+#    #+#             */
/*   Updated: 2017/03/23 18:53:33 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Renderer.hpp"
#include <sstream>


SDLRenderer::SDLRenderer()
{
}

SDLRenderer::~SDLRenderer()
{
}

SDLRenderer::SDLRenderer(const SDLRenderer &src)
{
	*this = src;
}

SDLRenderer	&SDLRenderer::operator=(const SDLRenderer &src)
{
	if (this != &src)
	{
		_window = src.getWindow();
		_renderer = src.getRenderer();
		_over = src.getOver();
		_text = src.getText();
		_width = src.getWidth();
		_height = src.getHeight();
	}
	return *this;
}

SDL_Window	*SDLRenderer::getWindow() const { return _window; }

SDL_Renderer	*SDLRenderer::getRenderer() const { return _renderer; }

SDL_Surface		*SDLRenderer::getOver() const { return _over; }

SDL_Texture		*SDLRenderer::getText() const { return _text; }

int				SDLRenderer::getWidth() const { return _width; }

int				SDLRenderer::getHeight() const { return _height; }


void	SDLRenderer::drawLimits() const
{
	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
	SDL_Rect		r1;
	r1.x = 0;
	r1.y = 0;
	r1.h = _height * SQUARE_LEN;
	r1.w = SQUARE_LEN;

	SDL_Rect		r2;
	r2.x = (_width - 1) * SQUARE_LEN;
	r2.y = 0;
	r2.h = _height * SQUARE_LEN;
	r2.w = SQUARE_LEN;

	SDL_Rect		r3;
	r3.x = 0;
	r3.y = 0;
	r3.h = SQUARE_LEN;
	r3.w = _width * SQUARE_LEN;

	SDL_Rect		r4;
	r4.x = 0;
	r4.y = (_height - 1) * SQUARE_LEN;
	r4.h = SQUARE_LEN;
	r4.w = _width * SQUARE_LEN;

	SDL_RenderFillRect(_renderer, &r1);
	SDL_RenderFillRect(_renderer, &r2);
	SDL_RenderFillRect(_renderer, &r3);
	SDL_RenderFillRect(_renderer, &r4);
}

bool SDLRenderer::init(int windw_w, int windw_h)
{
	_width = windw_w + 2;
	_height = windw_h + 2;
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cerr << SDL_GetError() << std::endl;
		return (false);
	}
	_window = SDL_CreateWindow("Nibbler", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, _width * SQUARE_LEN, _height * SQUARE_LEN, 0);
	if (!_window)
	{
		std::cerr << SDL_GetError()  << std::endl;
		return  (false);
	}
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED |
			SDL_RENDERER_PRESENTVSYNC);
	if (!_renderer)
	{
		std::cerr << SDL_GetError()  << std::endl;
		return  (false);
	}

	_over = SDL_LoadBMP("./sdl/Game_over.bmp");
	if (!_over)
	{
		std::cout << SDL_GetError() <<std::endl;
		return false;
	}
	uint8_t r, g, b;
	SDL_GetRGB(1, _over->format, &r, &g, &b);
	SDL_SetColorKey(_over, SDL_FALSE, SDL_MapRGB(_over->format, r, g, b));
	_text = SDL_CreateTextureFromSurface(_renderer, _over);

	return (true);
}

E_EVENT_TYPE	SDLRenderer::getLastEvent(void)
{
	SDL_Event	event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
		case SDL_QUIT:
			return (E_EVENT_TYPE::QUIT);
			break;
		case SDL_KEYDOWN:
			{
				switch (event.key.keysym.sym)
				{
					case (SDLK_UP):
						return (E_EVENT_TYPE::UP);
					case (SDLK_DOWN):
						return (E_EVENT_TYPE::DOWN);
					case (SDLK_LEFT):
						return (E_EVENT_TYPE::LEFT);
					case (SDLK_RIGHT):
						return (E_EVENT_TYPE::RIGHT);
					case (SDLK_w):
						return (E_EVENT_TYPE::W);
					case (SDLK_s):
						return (E_EVENT_TYPE::S);
					case (SDLK_a):
						return (E_EVENT_TYPE::A);
					case (SDLK_d):
						return (E_EVENT_TYPE::D);
					case (SDLK_ESCAPE):
						return (E_EVENT_TYPE::QUIT);
					case (SDLK_SPACE):
						return (E_EVENT_TYPE::SPACE);
					case (SDLK_r):
						return (E_EVENT_TYPE::RESTART);
					case (SDLK_1):
						return (E_EVENT_TYPE::LOAD_LIBRARY_ONE);
					case (SDLK_2):
						return (E_EVENT_TYPE::LOAD_LIBRARY_TWO);
					case (SDLK_3):
						return (E_EVENT_TYPE::LOAD_LIBRARY_THREE);
					break;
				}
				break;
			}
		default:
			return (E_EVENT_TYPE::UNKNOWN);
			break;
	}
	return (E_EVENT_TYPE::UNKNOWN);
}

void	SDLRenderer::render(void) const
{
	drawLimits();
	SDL_RenderPresent(_renderer);
}

void	SDLRenderer::drawP1Snake(Snake *snake) const
{
	SDL_SetRenderDrawColor(_renderer, 0, 255, 0, 255);
	SDL_Rect		r;

	r.x = (snake->getPos().first + 1) * SQUARE_LEN;
	r.y = (snake->getPos().second + 1) * SQUARE_LEN;
	r.h = SQUARE_LEN;
	r.w = SQUARE_LEN;
	SDL_RenderFillRect(_renderer, &r);
}

void	SDLRenderer::drawP1SnakeHead(Snake *snake) const
{
	SDL_SetRenderDrawColor(_renderer, 255, 0, 255, 255);
	SDL_Rect		r;

	r.x = (snake->getPos().first + 1) * SQUARE_LEN;
	r.y = (snake->getPos().second + 1) * SQUARE_LEN;
	r.h = SQUARE_LEN;
	r.w = SQUARE_LEN;
	SDL_RenderFillRect(_renderer, &r);
}

void	SDLRenderer::drawP2Snake(Snake *snake) const
{
	SDL_SetRenderDrawColor(_renderer, 0, 0, 255, 255);
	SDL_Rect		r;

	r.x = (snake->getPos().first + 1) * SQUARE_LEN;
	r.y = (snake->getPos().second + 1) * SQUARE_LEN;
	r.h = SQUARE_LEN;
	r.w = SQUARE_LEN;
	SDL_RenderFillRect(_renderer, &r);
}

void	SDLRenderer::drawP2SnakeHead(Snake *snake) const
{
	SDL_SetRenderDrawColor(_renderer, 100, 100, 255, 255);
	SDL_Rect		r;

	r.x = (snake->getPos().first + 1) * SQUARE_LEN;
	r.y = (snake->getPos().second + 1) * SQUARE_LEN;
	r.h = SQUARE_LEN;
	r.w = SQUARE_LEN;
	SDL_RenderFillRect(_renderer, &r);
}

void	SDLRenderer::drawFood(Food *food) const
{
	SDL_SetRenderDrawColor(_renderer, 255, 255, 0, 255);
	SDL_Rect		r;

	r.x = (food->getPos().first + 1) * SQUARE_LEN;
	r.y = (food->getPos().second + 1) * SQUARE_LEN;
	r.h = SQUARE_LEN;
	r.w = SQUARE_LEN;
	SDL_RenderFillRect(_renderer, &r);
}

void	SDLRenderer::drawSpecFood(SpecialFood *food) const
{
	SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255);
	SDL_Rect		r;

	r.x = (food->getPos().first + 1) * SQUARE_LEN;
	r.y = (food->getPos().second + 1) * SQUARE_LEN;
	r.h = SQUARE_LEN;
	r.w = SQUARE_LEN;
	SDL_RenderFillRect(_renderer, &r);
}

void	SDLRenderer::drawScore(size_t score) const
{ 	
	std::stringstream ss;
	ss << score;
	std::string str = "SCORE : " + ss.str();
	SDL_SetWindowTitle(_window, str.c_str());
}

void	SDLRenderer::drawGO() const
{
	SDL_Rect destZ = {SQUARE_LEN, SQUARE_LEN, (_width - 2) * SQUARE_LEN, (_height - 2) * SQUARE_LEN};
	SDL_RenderCopy(_renderer, _text, NULL, &destZ);
}

void	SDLRenderer::clearScreen(void) const
{
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
	SDL_RenderClear(_renderer);
}

bool SDLRenderer::close()
{
	SDL_FreeSurface(_over);
	SDL_DestroyTexture(_text);
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	SDL_Quit();
	return (false);
}
