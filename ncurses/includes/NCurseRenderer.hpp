/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NCurseRender.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 14:23:38 by tlepeche          #+#    #+#             */
/*   Updated: 2017/03/06 17:30:36 by tiboitel         ###   ########.fr       */
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
		bool			render() const;
		void			clearScreen() const;
		bool			close();

	private:
		WINDOW			*_window;
		bool			_IsCurseInit;

};

extern "C"
{
	IRenderer	*create_renderer()
	{
		return (new NCurseRenderer());
	}
}

#endif
