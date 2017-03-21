/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NCurseRender.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 14:23:38 by tlepeche          #+#    #+#             */
/*   Updated: 2017/03/21 15:46:14 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef NCURSERENDERER_HPP
# define NCURSERENDERER_HPP

#include <iostream>
#include <IRenderer.hpp>
#include <Snake.hpp>
#include <Food.hpp>
#include <SpecialFood.hpp>

class NCurseRenderer : public IRenderer
{

	public :
		NCurseRenderer();
		~NCurseRenderer(); 
		NCurseRenderer(const NCurseRenderer &src);
		NCurseRenderer	&operator=(const NCurseRenderer &src);

		WINDOW			*getWindow() const;
		bool			getIsInit() const;
		int				getHeight() const;
		int				getWidth() const;

		bool			init(int wind_w, int wind_h);
		E_EVENT_TYPE	getLastEvent();
		void			drawSnake(Snake *snake) const;
		void			drawSnakeHead(Snake	*snake) const;
		void			drawFood(Food *food) const;
		void			drawSpecFood(SpecialFood *food) const;
		void			drawScore(size_t score) const;
		void			drawGO() const;
		void			render() const;
		void			clearScreen() const;
		bool			close();
		void			drawLimits() const;

	private:
		WINDOW			*_window;
		bool			_isCurseInit;
		int				_height;
		int				_width;

};

extern "C"
{
	IRenderer	*create_renderer()
	{
		return (new NCurseRenderer());
	}
}

#endif
