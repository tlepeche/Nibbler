/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRenderer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 15:42:42 by tiboitel          #+#    #+#             */
/*   Updated: 2017/03/23 18:51:09 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IRENDERER_HPP
# define FT_IRENDERER_HPP

#include "Snake.hpp"
#include "Food.hpp"
#include "SpecialFood.hpp"

typedef enum class	e_event_type
{
	UP, RIGHT, LEFT, DOWN,
	W, D, A, S,
	QUIT, PAUSED, SPACE, RESTART,
	LOAD_LIBRARY_ONE, LOAD_LIBRARY_TWO,	LOAD_LIBRARY_THREE,
	RESIZE, UNKNOWN
}					E_EVENT_TYPE;

class IRenderer
{
	public:
		virtual 				~IRenderer() {};
		virtual bool			init(int windw_w, int windw_h) = 0;
		virtual E_EVENT_TYPE	getLastEvent(void) = 0;

		virtual void			drawP1Snake(Snake	*snake) const = 0;
		virtual void			drawP1SnakeHead(Snake	*snake) const = 0;
		virtual void			drawP2Snake(Snake	*snake) const = 0;
		virtual void			drawP2SnakeHead(Snake	*snake) const = 0;

		virtual void			drawFood(Food *food) const = 0;
		virtual void			drawSpecFood(SpecialFood *food) const = 0;
		virtual void			drawScore(size_t score) const = 0;
		virtual void			drawGO() const = 0;
		virtual void			render(void) const = 0;
		virtual void			clearScreen(void) const = 0;
		virtual bool 			close(void) = 0;
};

#endif
