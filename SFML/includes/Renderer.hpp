/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Renderer.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 15:55:13 by tiboitel          #+#    #+#             */
/*   Updated: 2017/03/23 18:51:20 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_RENDERER_HPP
# define FT_RENDERER_HPP

#include <SFML/Graphics.hpp>
#include "IRenderer.hpp"
#include "Snake.hpp"
#include "Food.hpp"

#define SQUARE_LEN 16
class SFMLRenderer : public IRenderer
{
	public:
		SFMLRenderer();
		~SFMLRenderer();
		SFMLRenderer(const SFMLRenderer &src);
		SFMLRenderer	&operator=(const SFMLRenderer &src);

		sf::RenderWindow	*getWindow() const;
		int					getHeight() const;
		int					getWidth() const;

		bool 			init(int windw_w, int windw_h);
		bool 			close(void);
		void			render(void) const;
		void			clearScreen(void) const;
		void			drawP1Snake(Snake *snake) const;
		void			drawP1SnakeHead(Snake	*snake) const;
		void			drawP2Snake(Snake *snake) const;
		void			drawP2SnakeHead(Snake	*snake) const;
		void			drawFood(Food *food) const;
		void			drawLimits() const;
		void			drawSpecFood(SpecialFood *food) const;
		void			drawGO() const;
		void			drawScore(size_t score) const;
		E_EVENT_TYPE	getLastEvent(void);
		E_EVENT_TYPE	check(sf::Event event);

	private:
		sf::RenderWindow	*_window;
		int					_height;
		int					_width;
};

extern "C"
{
	IRenderer	*create_renderer()
	{
		return (new SFMLRenderer());
	}
}
#endif
