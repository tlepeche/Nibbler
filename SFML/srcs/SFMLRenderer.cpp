/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SFMLRenderer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 10:36:49 by tlepeche          #+#    #+#             */
/*   Updated: 2017/03/23 18:51:06 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Renderer.hpp>
#include <sstream>

SFMLRenderer::SFMLRenderer() {}

SFMLRenderer::~SFMLRenderer() {}

SFMLRenderer::SFMLRenderer(const SFMLRenderer &src)
{
	*this= src;
}

SFMLRenderer	&SFMLRenderer::operator=(const SFMLRenderer &src)
{
	if (this != &src)
	{
		_window = getWindow();
		_height = getHeight();
		_width = getWidth();
	}
	return *this;
}

sf::RenderWindow	*SFMLRenderer::getWindow() const { return _window; }

int					SFMLRenderer::getHeight() const { return _height; }

int					SFMLRenderer::getWidth() const { return _width; }

void	SFMLRenderer::drawLimits() const
{
	sf::RectangleShape rectangle(sf::Vector2f(SQUARE_LEN, SQUARE_LEN * _height));
	rectangle.setFillColor(sf::Color(255, 255, 255));
	rectangle.setPosition(0, 0);
	_window->draw(rectangle);
	rectangle.setPosition((_width - 1) * SQUARE_LEN, 0);
	_window->draw(rectangle);

	sf::RectangleShape rectangle2(sf::Vector2f(SQUARE_LEN * _width, SQUARE_LEN));
	rectangle2.setFillColor(sf::Color(255, 255, 255));
	rectangle2.setPosition(0, 0);
	_window->draw(rectangle2);
	rectangle2.setPosition(0, (_height - 1) * SQUARE_LEN);
	_window->draw(rectangle2);
}

bool SFMLRenderer::init(int windw_w, int windw_h)
{
	_height = windw_h + 2;
	_width = windw_w + 2;
	_window = new sf::RenderWindow(sf::VideoMode(_width * SQUARE_LEN, _height * SQUARE_LEN),
			"Snake", sf::Style::Titlebar);
	if (!_window)
		return false;
	return true;
}

E_EVENT_TYPE	SFMLRenderer::check(sf::Event event)
{
	switch (event.key.code)
	{
		case (sf::Keyboard::Escape):
			return E_EVENT_TYPE::QUIT;
		case (sf::Keyboard::Space):
			return E_EVENT_TYPE::SPACE;
		case (sf::Keyboard::R):
			return E_EVENT_TYPE::RESTART;
		case (sf::Keyboard::Num1):
			return E_EVENT_TYPE::LOAD_LIBRARY_ONE;
		case (sf::Keyboard::Num2):
			return E_EVENT_TYPE::LOAD_LIBRARY_TWO;
		case (sf::Keyboard::Num3):
			return E_EVENT_TYPE::LOAD_LIBRARY_THREE;
		case (sf::Keyboard::Up):
			return E_EVENT_TYPE::UP;
		case (sf::Keyboard::Down):
			return E_EVENT_TYPE::DOWN;
		case (sf::Keyboard::Left):
			return E_EVENT_TYPE::LEFT;
		case (sf::Keyboard::Right):
			return E_EVENT_TYPE::RIGHT;
		case (sf::Keyboard::W):
			return E_EVENT_TYPE::W;
		case (sf::Keyboard::S):
			return E_EVENT_TYPE::S;
		case (sf::Keyboard::D):
			return E_EVENT_TYPE::D;
		case (sf::Keyboard::A):
			return E_EVENT_TYPE::A;
		default:
			return E_EVENT_TYPE::UNKNOWN;
			break;
	}
}

E_EVENT_TYPE	SFMLRenderer::getLastEvent()
{
	sf::Event event;
	if (_window->pollEvent(event))
	{
		switch (event.type)
		{
			case (sf::Event::Closed):
				return E_EVENT_TYPE::QUIT;
			case (sf::Event::KeyPressed):
				return check(event);
			default:
				return E_EVENT_TYPE::UNKNOWN;
				break;
		}
	}
	return E_EVENT_TYPE::UNKNOWN;
}

void			SFMLRenderer::render() const
{
	drawLimits();
	_window->display();
}

void	SFMLRenderer::drawP1Snake(Snake *snake) const
{
	sf::RectangleShape rectangle(sf::Vector2f(SQUARE_LEN, SQUARE_LEN));

	rectangle.setFillColor(sf::Color(0, 255, 0));
	rectangle.setPosition((snake->getPos().first + 1) * SQUARE_LEN, (snake->getPos().second + 1) * SQUARE_LEN);
	_window->draw(rectangle);
}

void	SFMLRenderer::drawP1SnakeHead(Snake *snake) const
{
	sf::RectangleShape rectangle(sf::Vector2f(SQUARE_LEN, SQUARE_LEN));

	rectangle.setFillColor(sf::Color(255, 0, 255));
	rectangle.setPosition((snake->getPos().first + 1) * SQUARE_LEN, (snake->getPos().second + 1) * SQUARE_LEN);
	_window->draw(rectangle);
}

void	SFMLRenderer::drawP2Snake(Snake *snake) const
{
	sf::RectangleShape rectangle(sf::Vector2f(SQUARE_LEN, SQUARE_LEN));

	rectangle.setFillColor(sf::Color(0, 0, 255));
	rectangle.setPosition((snake->getPos().first + 1) * SQUARE_LEN, (snake->getPos().second + 1) * SQUARE_LEN);
	_window->draw(rectangle);
}

void	SFMLRenderer::drawP2SnakeHead(Snake *snake) const
{
	sf::RectangleShape rectangle(sf::Vector2f(SQUARE_LEN, SQUARE_LEN));

	rectangle.setFillColor(sf::Color(100, 100, 255));
	rectangle.setPosition((snake->getPos().first + 1) * SQUARE_LEN, (snake->getPos().second + 1) * SQUARE_LEN);
	_window->draw(rectangle);
}

void	SFMLRenderer::drawFood(Food *food) const
{
	sf::RectangleShape rectangle(sf::Vector2f(SQUARE_LEN, SQUARE_LEN));

	rectangle.setFillColor(sf::Color(255, 255, 0));
	rectangle.setPosition((food->getPos().first + 1) * SQUARE_LEN, (food->getPos().second + 1) * SQUARE_LEN);
	_window->draw(rectangle);
}

void	SFMLRenderer::drawSpecFood(SpecialFood *food) const
{
	sf::RectangleShape rectangle(sf::Vector2f(SQUARE_LEN, SQUARE_LEN));

	rectangle.setFillColor(sf::Color(255, 0, 0));
	rectangle.setPosition((food->getPos().first + 1) * SQUARE_LEN, (food->getPos().second + 1) * SQUARE_LEN);
	_window->draw(rectangle);
}

void	SFMLRenderer::drawScore(size_t score) const
{
	std::stringstream ss;
	ss << score;
	std::string str = "SCORE : " + ss.str();
	_window->setTitle(str);
}

void	SFMLRenderer::drawGO() const
{
	sf::Font font;
	if (font.loadFromFile("./SFML/sansation.ttf"))
	{
		sf::Text text;
		text.setFont(font);
		text.setString("GAME OVER");
		text.setCharacterSize(_width);
		text.setColor(sf::Color::White);
		text.setStyle(sf::Text::Bold);
		text.setPosition((_width * SQUARE_LEN) / 2 - (_width * 3), (_height * (SQUARE_LEN - 1)) / 2);
		_window->draw(text);
	}
}

void	SFMLRenderer::clearScreen() const
{
	_window->clear();
}

bool	SFMLRenderer::close()
{
	_window->close();
	delete _window;
	return true;
}
