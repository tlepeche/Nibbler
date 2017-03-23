/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NCurseRenderer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 14:19:45 by tlepeche          #+#    #+#             */
/*   Updated: 2017/03/23 18:52:56 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>
#include <NCurseRenderer.hpp>
#include <sstream>

NCurseRenderer::NCurseRenderer(): _isCurseInit(false)
{}

NCurseRenderer::~NCurseRenderer() {}

NCurseRenderer::NCurseRenderer(const NCurseRenderer &src)
{
	*this = src;
}

NCurseRenderer	&NCurseRenderer::operator=(const NCurseRenderer &src)
{
	if (this != &src)
	{
		_window = src.getWindow();
		_isCurseInit = src.getIsInit();
		_height = src.getHeight();
		_width = src.getWidth();
	}
	return *this;
}

WINDOW			*NCurseRenderer::getWindow() const { return _window; }

bool			NCurseRenderer::getIsInit() const { return _isCurseInit; }

int				NCurseRenderer::getHeight() const { return _height; }

int				NCurseRenderer::getWidth() const { return _width; }

void			NCurseRenderer::drawLimits() const
{
	int i = 0;
	while (i < _width)
	{
		attron(COLOR_PAIR(1));
		mvprintw(1, i, "#");
		mvprintw(_height, i, "#");
		attroff(COLOR_PAIR(1));
		i++;
	}
	int j = 1;
	while (j < _height + 1)
	{
		attron(COLOR_PAIR(1));
		mvprintw(j, 0, "#");
		mvprintw(j, _width - 1, "#");
		attroff(COLOR_PAIR(1));
		j++;
	}
}

bool	NCurseRenderer::init(int wind_w, int wind_h)
{
	if (_isCurseInit)
		refresh();
	else
	{
		_width = wind_w + 2;
		_height = wind_h + 2;
		initscr();
		cbreak(); //allow only one character at a time input
		noecho(); //stop inputs echoing
		nodelay(stdscr, true); //allow function getch() to be non-blocking function
		keypad(stdscr, true); //allow to capture special key (delete, backspace and 4 arrows)
		curs_set(0); //set cursor to be invisible
		intrflush(stdscr, false); //prevent input queuing
		timeout(0); //prevent delay reading
		start_color();
		init_pair(1, COLOR_WHITE, COLOR_WHITE); //WALL
		init_pair(2, COLOR_YELLOW, COLOR_YELLOW); // FOOD
		init_pair(3, COLOR_GREEN, COLOR_GREEN); // P1SNAKE
		init_pair(4, COLOR_RED, COLOR_RED); // SPECIALFOOD
		init_pair(5, COLOR_MAGENTA, COLOR_MAGENTA); // P1SNAKEHEAD
		init_pair(6, COLOR_BLUE, COLOR_BLUE); // P2SNAKE
		init_pair(7, COLOR_CYAN, COLOR_CYAN); // P2SNAKEHEAD
		_window = newwin(_width, _height + 1, 0, 0);
		_isCurseInit = true;
		return true;
	}
	return false;
}

E_EVENT_TYPE NCurseRenderer::getLastEvent()
{
	int ch = getch();
	int x, y;
	getmaxyx(stdscr, y, x);
	if (x < _width + 1 || y < _height + 2)
	{
		clear();
		mvprintw(y / 2, x / 2 - 10, "Window is too small to play");
		mvprintw(y / 2 + 1, x / 2 - 2, "Game paused");
		mvprintw(y / 2 + 2, x / 2 - 2, "X = %d(min %d), Y= %d(min %d)", x, _width + 1, y, _height + 2);
		refresh();
		return (E_EVENT_TYPE::RESIZE);
	}
	switch (ch)
	{
		case (49):
			return (E_EVENT_TYPE::LOAD_LIBRARY_ONE);
			break;
		case (50):
			return (E_EVENT_TYPE::LOAD_LIBRARY_TWO);
			break;
		case (51):
			return (E_EVENT_TYPE::LOAD_LIBRARY_THREE);
			break;
		case ('r'):
			return (E_EVENT_TYPE::RESTART);
			break;
		case ('w'):
			return (E_EVENT_TYPE::W);
			break;
		case ('a'):
			return (E_EVENT_TYPE::A);
			break;
		case ('s'):
			return (E_EVENT_TYPE::S);
			break;
		case ('d'):
			return (E_EVENT_TYPE::D);
			break;
		case KEY_UP:
			return (E_EVENT_TYPE::UP);
			break;
		case KEY_DOWN:
			return (E_EVENT_TYPE::DOWN);
			break;
		case KEY_LEFT:
			return (E_EVENT_TYPE::LEFT);
			break;
		case KEY_RIGHT:
			return (E_EVENT_TYPE::RIGHT);
			break;
		case (27):
			return (E_EVENT_TYPE::QUIT);
			break;
		case (' '):
			return (E_EVENT_TYPE::SPACE);
			break;
		default :
			return (E_EVENT_TYPE::UNKNOWN);
			break;
	}
	return (E_EVENT_TYPE::UNKNOWN);
}

void	NCurseRenderer::render() const
{
	drawLimits();
	refresh();
}

void	NCurseRenderer::drawFood(Food *food) const
{
	attron(COLOR_PAIR(2));
	mvprintw(food->getPos().second + 2, food->getPos().first + 1, "#");
	attroff(COLOR_PAIR(2));
}

void	NCurseRenderer::drawSpecFood(SpecialFood *food) const
{
	attron(COLOR_PAIR(4));
	mvprintw(food->getPos().second + 2, food->getPos().first + 1, "#");
	attroff(COLOR_PAIR(4));
}

void	NCurseRenderer::drawP1Snake(Snake *snake) const
{
	attron(COLOR_PAIR(3));
	mvprintw(snake->getPos().second + 2, snake->getPos().first + 1, "#");
	attroff(COLOR_PAIR(3));
}

void	NCurseRenderer::drawP1SnakeHead(Snake *snake) const
{
	attron(COLOR_PAIR(5));
	mvprintw(snake->getPos().second + 2, snake->getPos().first + 1, "#");
	attroff(COLOR_PAIR(5));
}

void	NCurseRenderer::drawP2Snake(Snake *snake) const
{
	attron(COLOR_PAIR(6));
	mvprintw(snake->getPos().second + 2, snake->getPos().first + 1, "#");
	attroff(COLOR_PAIR(6));
}

void	NCurseRenderer::drawP2SnakeHead(Snake *snake) const
{
	attron(COLOR_PAIR(7));
	mvprintw(snake->getPos().second + 2, snake->getPos().first + 1, "#");
	attroff(COLOR_PAIR(7));
}

void	NCurseRenderer::drawScore(size_t score) const
{
	std::stringstream ss;
	ss << score;	
	std::string scoring = "SCORE : " + ss.str() ;
	mvprintw(0, (_width - scoring.size()) / 2, scoring.c_str());
}

void	NCurseRenderer::drawGO() const
{
	mvprintw(_height / 2, _width / 2 - 4, "GAME OVER");
}

void	NCurseRenderer::clearScreen() const
{
	clear();
}

bool	NCurseRenderer::close()
{
	if (!isendwin() && _isCurseInit)
	{
		_isCurseInit = false;
		endwin();
		return true;
	}
	return false;
}
