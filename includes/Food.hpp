/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Food.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 21:01:19 by tiboitel          #+#    #+#             */
/*   Updated: 2017/03/03 19:24:43 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FOOD_HPP
# define FT_FOOD_HPP

# include <AEntity.hpp>


class Food : public virtual AEntity
{
	public:
		Food(int x, int y);
		~Food();
		Food		(Food const &rhs);
		Food		&operator=(Food const &rhs);
	private:
		Food();
};

#endif
