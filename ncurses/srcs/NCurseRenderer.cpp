/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NCurseRenderer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 14:19:45 by tlepeche          #+#    #+#             */
/*   Updated: 2017/03/06 17:31:27 by tiboitel         ###   ########.fr       */
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
		/*	init_pair(3, COLOR_WHITE, COLOR_BLACK);
			init_pair(4, COLOR_CYAN, COLOR_BLACK);
			init_pair(5, COLOR_GREEN, COLOR_BLACK);
			init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
			init_pair(7, COLOR_BLUE, COLOR_BLACK);*/
		_window = newwin(wind_w, wind_h * 2, 0, 0);
		_IsCurseInit = true;
	}
	endwin();
	return true;
}

E_EVENT_TYPE NCurseRenderer::getLastEvent()
{
	int ch = getch();
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

bool	NCurseRenderer::render() const
{
	refresh();
	return (true);
}

void	NCurseRenderer::drawFood(Food *food) const
{
	int y = 0;
	while (y < 1)
	{
		int x = 0;
		while (x < 2)
		{
			move(food->getPos().second + y, food->getPos().first + x);	
			attron(COLOR_PAIR(2));
			printw("#");
			attroff(COLOR_PAIR(2));
			x++;
		}
		y++;
	}
}

void	NCurseRenderer::drawSnake(Snake *snake) const
{
	int y = 0;
	while (y < 1)
	{
		int x = 0;
		while (x < 2)
		{
			move(snake->getPos().second + y, snake->getPos().first + x);	
			attron(COLOR_PAIR(1));
			printw("#");
			attroff(COLOR_PAIR(1));
			x++;
		}
		y++;
	}
}

void	NCurseRenderer::clearScreen() const
{
	clear();
	refresh();
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
