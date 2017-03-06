/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NCurseRenderer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 14:19:45 by tlepeche          #+#    #+#             */
/*   Updated: 2017/03/06 19:21:33 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>
#include <NCurseRenderer.hpp>

NCurseRenderer::NCurseRenderer(): _IsCurseInit(false)
{}

NCurseRenderer::~NCurseRenderer() {}

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
		_window = newwin(_width, _height, 0, 0);
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
		case ('q'):
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
	refresh();
}

void	NCurseRenderer::drawFood(Food *food) const
{
	move(food->getPos().second, food->getPos().first);	
	attron(COLOR_PAIR(2));
	printw("#");
	attroff(COLOR_PAIR(2));
}

void	NCurseRenderer::drawSnake(Snake *snake) const
{
	move(snake->getPos().second, snake->getPos().first);	
	attron(COLOR_PAIR(1));
	printw("#");
	attroff(COLOR_PAIR(1));
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
