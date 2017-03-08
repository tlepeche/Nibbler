/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Food.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 21:01:19 by tiboitel          #+#    #+#             */
/*   Updated: 2017/03/08 18:41:56 by tlepeche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FOOD_HPP
# define FT_FOOD_HPP

# include <AEntity.hpp>


class Food : public virtual AEntity
{
	public:
		Food(int x, int y, size_t score = 200);
		~Food();
		Food		(Food const &rhs);
		Food		&operator=(Food const &rhs);
		size_t		getScore() const;

	protected:
		Food();
		size_t		_score;
};

#endif
