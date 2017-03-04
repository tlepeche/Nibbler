/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRenderer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 15:42:42 by tiboitel          #+#    #+#             */
/*   Updated: 2017/03/04 19:33:44 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IRENDERER_HPP
# define FT_IRENDERER_HPP

#include "Snake.hpp"
#include "Food.hpp"

typedef enum class	e_event_type
{
	UP, RIGHT, LEFT, DOWN, 	QUIT, UNKNOWN
}					E_EVENT_TYPE;

class IRenderer
{
	public:
		virtual 				~IRenderer() {};
		virtual bool			init(int windw_w, int windw_h) = 0;
		virtual E_EVENT_TYPE	getLastEvent(void) = 0;
		virtual void			drawSnake(Snake	*snake) const = 0;
		virtual void			drawFood(Food *food) const = 0;
		virtual void			render(void) const = 0;
		virtual void			clear(void) const = 0;
		virtual bool 			close(void) = 0;
	private:
};

#endif
