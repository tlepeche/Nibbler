/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SFMLRenderer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 10:36:49 by tlepeche          #+#    #+#             */
/*   Updated: 2017/03/13 11:34:10 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Renderer.hpp>

SFMLRenderer::SFMLRenderer() {}

SFMLRenderer::~SFMLRenderer() {}

bool SFMLRenderer::init(int windw_w, int windw_h)
{
	_window = new sf::RenderWindow(sf::VideoMode(windw_w, windw_h), "Snake");
	return true;
}

E_EVENT_TYPE	SFMLRenderer::getLastEvent()
{
	sf::Event event;
	_window->pollEvent(event);

	switch (event.type)
	{
		case (sf::Event::Closed):
			return E_EVENT_TYPE::QUIT;
		case (sf::Event::KeyPressed):
			if (event.key.code == sf::Keyboard::Escape)
				return E_EVENT_TYPE::QUIT;
			if (event.key.code == sf::Keyboard::Up)
				return E_EVENT_TYPE::UP;
			if (event.key.code == sf::Keyboard::Down)
				return E_EVENT_TYPE::DOWN;
			if (event.key.code == sf::Keyboard::Left)
				return E_EVENT_TYPE::LEFT;
			if (event.key.code == sf::Keyboard::Right)
				return E_EVENT_TYPE::RIGHT;
			if (event.key.code == sf::Keyboard::Num1)
				return E_EVENT_TYPE::LOAD_LIBRARY_ONE;
			if (event.key.code == sf::Keyboard::Num2)
				return E_EVENT_TYPE::LOAD_LIBRARY_TWO;
			if (event.key.code == sf::Keyboard::Num3)
				return E_EVENT_TYPE::LOAD_LIBRARY_THREE;
			break;
		default:
			return E_EVENT_TYPE::UNKNOWN;
			break;
	}
	return E_EVENT_TYPE::UNKNOWN;

}

void			SFMLRenderer::render() const
{
	_window->display();
}

void	SFMLRenderer::drawSnake(Snake *snake) const
{
	sf::RectangleShape rectangle(sf::Vector2f(SQUARE_LEN, SQUARE_LEN));

	rectangle.setFillColor(sf::Color(255, 255, 255));
	rectangle.setPosition(snake->getPos().first * SQUARE_LEN, snake->getPos().second * SQUARE_LEN);
	_window->draw(rectangle);
}

void	SFMLRenderer::drawFood(Food *food) const
{
	sf::RectangleShape rectangle(sf::Vector2f(SQUARE_LEN, SQUARE_LEN));

	rectangle.setFillColor(sf::Color(255, 255, 0));
	rectangle.setPosition(food->getPos().first * SQUARE_LEN, food->getPos().second * SQUARE_LEN);
	_window->draw(rectangle);
}

void	SFMLRenderer::drawSpecFood(SpecialFood *food) const
{
	sf::RectangleShape rectangle(sf::Vector2f(SQUARE_LEN, SQUARE_LEN));

	rectangle.setFillColor(sf::Color(255, 0, 0));
	rectangle.setPosition(food->getPos().first * SQUARE_LEN, food->getPos().second * SQUARE_LEN);
	_window->draw(rectangle);
}

void	SFMLRenderer::drawScore(size_t score) const
{
	(void)score;

}

void	SFMLRenderer::drawGO() const
{

}

void	SFMLRenderer::clearScreen() const
{
	_window->clear();
}

bool	SFMLRenderer::close()
{
	_window->close();
	return true;
}
