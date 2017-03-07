/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NCurseRenderer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 14:19:45 by tlepeche          #+#    #+#             */
/*   Updated: 2017/03/07 17:29:12 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>
#include <NCurseRenderer.hpp>

NCurseRenderer::NCurseRenderer(): _IsCurseInit(false)
{}

NCurseRenderer::~NCurseRenderer() {}

void	NCurseRenderer::drawLimits() const
{
	int i = 0;
	while (i <= _width + 1)
	{
		attron(COLOR_PAIR(1));
		mvprintw(0, i, "#");
		mvprintw(_height + 1, i, "#");
		attroff(COLOR_PAIR(1));
		i++;
	}
	int j = 0;
	while (j <= _height + 1)
	{
		attron(COLOR_PAIR(1));
		mvprintw(j, 0, "#");
		mvprintw(j, _width + 1, "#");
		attroff(COLOR_PAIR(1));
		j++;
	}
}

bool	NCurseRenderer::init(int wind_w, int wind_h)
{
	if (_IsCurseInit)
		refresh();
	else
	{
		_width = wind_w;
		_height = wind_h;
		initscr();
		cbreak(); //allow only one character at a time input
		noecho(); //stop inputs echoing
		nodelay(stdscr, true); //allow function getch() to be non-blocking function
		keypad(stdscr, true); //allow to capture special key (delete, backspace and 4 arrows)
		curs_set(0); //set cursor to be invisible
		intrflush(stdscr, false); //prevent input queuing
		timeout(0); //prevent delay reading
		start_color();
		init_pair(1, COLOR_WHITE, COLOR_WHITE); //SNAKE
		init_pair(2, COLOR_YELLOW, COLOR_YELLOW); // FOOD
		init_pair(3, COLOR_GREEN, COLOR_GREEN); // FOOD
		_window = newwin(_width+1, _height+1, 0, 0);
		_IsCurseInit = true;
		return true;
	}
	return false;
}

E_EVENT_TYPE NCurseRenderer::getLastEvent()
{
	int ch = getch();
	int x, y;
	getmaxyx(stdscr, y, x);
	if (x < _width || y < _height)
	{
		clear();
		mvprintw(y / 2, x / 2 - 10, "Window is too small to play");
		mvprintw(y / 2 + 1, x / 2 - 2, "Game paused");
		mvprintw(y / 2 + 2, x / 2 - 2, "X = %d(min %d), Y= %d(min %d)", x, _width, y, _height);
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
	mvprintw(food->getPos().second + 1, food->getPos().first + 1, "#");
	attroff(COLOR_PAIR(2));
}

void	NCurseRenderer::drawSnake(Snake *snake) const
{
	attron(COLOR_PAIR(3));
	mvprintw(snake->getPos().second + 1, snake->getPos().first + 1, "#");
	attroff(COLOR_PAIR(3));
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
	if (!isendwin() && _IsCurseInit)
	{
		_IsCurseInit = false;
		endwin();
		return true;
	}
	return false;
}
