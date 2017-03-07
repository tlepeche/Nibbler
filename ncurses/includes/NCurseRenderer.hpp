/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NCurseRender.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 14:23:38 by tlepeche          #+#    #+#             */
/*   Updated: 2017/03/07 17:18:15 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef NCURSERENDERER_HPP
# define NCURSERENDERER_HPP

#include <iostream>
#include <IRenderer.hpp>
#include <Snake.hpp>
#include <Food.hpp>

class NCurseRenderer : public IRenderer
{

	public :
		NCurseRenderer();
		~NCurseRenderer(); 
		bool			init(int wind_w, int wind_h);
		E_EVENT_TYPE	getLastEvent();
		void			drawSnake(Snake *snake) const;
		void			drawFood(Food *food) const;
		void			drawGO() const;
		void			render() const;
		void			clearScreen() const;
		bool			close();
		void			drawLimits() const;

	private:
		WINDOW			*_window;
		bool			_IsCurseInit;
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
